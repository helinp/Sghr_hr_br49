//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// ball velocity
double VELOCITY = 0.003;
double angle;
double dx, dy;

// dimensions & position of paddle in pixels
int paddle_h = 10;
int paddle_w = 40;
int paddle_y = 60;

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

void setAngleBall (double direction);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before starting
    waitForClick();
    
    // setting char for sprintf
    char s[12] = {0};
    
    // Show score
    updateScoreboard(window, label, points);
 
    // get random direction of ball
    angle = 45.0 + drand48() * 45;
    setAngleBall(angle);
 
    // keep playing until game over
    while (bricks > 0)
    {
        /**
         * Pad follows mouse
         */
         
        // check for mouse event
        GEvent mouse_event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (mouse_event != NULL)
        {
            // if the event was movement
            if (getEventType(mouse_event) == MOUSE_MOVED)
            {
                // ensure pad follows cursor
                setLocation(paddle, getX(mouse_event) - (paddle_w / 2), getY(paddle));
            }
        }
        
        
     
        /**
         * Moves and bounce the ball
         */
   
        // moves the ball
        move(ball, dx, dy);
            
        // collision detection
        GObject object = detectCollision(window, ball);       
                
                
        /**
         * Bouncing ball
         */
       
            if(object == paddle)
            {
           
                // reverses Y axis direction of ball
                dy = -dy; 
                
                
                /**
                 * Change rebound angle 
                 *
                 */
                 
                /** 
                 * WORK IN PROGRESS...
                 *
                 
                // set angle of ball from dy dx
                
                double angle_rad = atan(dy/dx);
                angle = angle_rad / 3.141592 * 180;
                
                
                int ball_x = getX(ball) + RADIUS;
                int paddle_x = getX(paddle) + (paddle_w / 2);
                
                // if touches left side of the paddle
                if(ball_x >= getX(paddle) && ball_x < paddle_x)
                {
                   // TODO get direction (dx) to determine + - angle
                    printf("Debug ball %i, paddle %i, angle %f  \n", ball_x, paddle_x, angle );
                    
                    // 100% -- 0% of changing angle 
                    double diff = (double) (ball_x - paddle_x) / (paddle_w / 2);
                    
                    if (angle <= -90)
                    {
                        angle = angle - 45 - (45 * diff);  
                    }
                    else 
                    {
                        angle = angle + 45 - (45 * diff); 
                    }
                    
                    
                    
                    printf("change %f\n", angle);  
                }
                
                // if ball goes to the right side of the paddle
                else if(ball_x > paddle_x )
                {
                    //printf("right %f\n",angle);
                    //angle = angle - 45 * ( getX(paddle) - getX(ball) + RADIUS) / ((paddle_w / 2)) ;
                }
                
                
                // gets dx dy coordinates from variable angle
                double radians = angle * 3.141592 / 180.0;
                double hyp = VELOCITY; 
                dx = cos(radians) * hyp;
                dy = sin(radians) * hyp; 
                 */           
            }
            
            
            // bounce off right OR left edge of window
            if (getX(ball) + RADIUS * 2 >= WIDTH
                || getX(ball) <= 0)
            {
                dx = -dx;
            }
                
            // bounce off top edge of window
            if (getY(ball)  <= 0)
            {
                dy = -dy;
            }
            
            /**
             * If ball goes off the bottom edge of window
             */
             
            else if ((getY(ball) + (2 * RADIUS))  >= HEIGHT)
            {
                // Freezes the ball
                move(ball, 0, 0);
                lives--;
                
                // ends loop if no more lives
                if (lives == 0)
                {
                    break;
                }
                
                // New ball
                waitForClick();
         
                // updates score 6 resets ball
                updateScoreboard(window, label, points);
                setLocation(ball, (WIDTH / 2) - RADIUS, (HEIGHT / 2) + RADIUS); 
            }
         
            
            /**
             * Breaks bricks
             *
             *
             */
             
            if(object != NULL && object != label && object != window && object != paddle)
            {
                
                dy = -dy;
                points++;
                bricks--;
                removeGWindow(window, object);
                updateScoreboard(window, label, points);
            }
           
    }
    
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    
    if (bricks <= 0)
    {
    // Game Over
        sprintf(s,"Winner");
        
        // center label in window
        setLocation(label, x - 80, y);
        setLabel(label,s);
    
    }
    else
    {
        // Game Over
        sprintf(s,"Game Over");
        
        // center label in window
        setLocation(label, x - 90, y);
        setLabel(label,s);
    }
    
    // wait for click before exiting
    waitForClick();

    closeGWindow(window);
    return 0;
}


/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
   
    
    for (int i = 0 ; i < ROWS ; i++)
    {
       for (int j = 0 ; j < COLS ; j++)
       {      
        GRect brick = newGRect(5 + (j * (WIDTH / COLS)), 50 + (i * 15), (WIDTH / COLS) - 5, 10);
        setFilled(brick, true);
        
        // Sets color of first half row
        if (i <= ROWS / 2)
        {
            setColor(brick, "#0000FF");
        }
        
        // Sets color of second half row
        else
        {
            setColor(brick, "GREEN");
        }
        
        add(window, brick);
        
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    
    GOval ball = newGOval((WIDTH / 2) - RADIUS, (HEIGHT / 2) + RADIUS, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO add paddle color variable
        
    GRect paddle = newGRect( (WIDTH - paddle_w) / 2 , HEIGHT + paddle_h - paddle_y, paddle_w, paddle_h);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
                
    return paddle;
   
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // Starting game
    GLabel score = newGLabel("Click to start");
    setFont(score, "SansSerif-32");
    double x = (getWidth(window) - getWidth(score)) / 2;
    double y = (getHeight(window) + getFontAscent(score)) / 2;
    setLocation(score, x, y);
    setColor(score, "GRAY");
    add(window, score);
    
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

void setAngleBall (double direction)
{
        // gets dx dy coordinates from variable angle
        double radians = direction * 3.141592 / 180.0;
        double hyp = VELOCITY ; 
        dx = cos(radians) * hyp;
        dy = sin(radians) * hyp;
}
