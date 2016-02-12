<!DOCTYPE html>

<html>
    <head>
        <title>hello</title>
    </head>
    <body>
        hello, 
<?php 

if(!empty($_GET["name"]) ) 
{
    echo htmlspecialchars($_GET["name"]); 
}
else 
{
    echo 'John Doe';
} 

?>

    </body>
</html>
