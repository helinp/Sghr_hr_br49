<?php
    
    require("../includes/config.php");
    
    // render form    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);            
    }
    
    // process buy 
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {    
    
        // declares variable
        $symbol = lookup($_POST["symbol"]);
      
        
        // Data check
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("All fields must be filled in."); 
        }       
        elseif ($symbol === false)
        {
            apologize("Symbol not found."); 
        }
        else
        {
            // opens database
            $user_data = query("SELECT * from users WHERE id = ?", $_SESSION["id"]);
            $buy_value = $_POST["shares"] * $symbol["price"];
            
            if ($user_data[0]["cash"] < $buy_value)
            {
                apologize("Insufficient cash flow, ask you mother for more money.");
            }
            else
            { 
                // updates database
                query("START TRANSACTION");
                query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol["symbol"], $_POST["shares"]);
                query("UPDATE users SET cash = cash - ? WHERE id = ? ", $buy_value, $_SESSION["id"]);
                history("BUY", $symbol["symbol"], $_POST["shares"]);
                query("COMMIT");
                
                // redirects to portfolio
                redirect("/");
            }
            
        }
        
    }
    
    
?>
