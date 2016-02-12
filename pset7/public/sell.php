<?php
    
    require("../includes/config.php");
    
    // opens portfolio table
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
  
    // renders sell template, if anything to sell
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {             
        if (empty($rows))
        {
            apologize("Your portfolio is empty!");
        } 
        else
        {
            foreach($rows as $row)
            {
                $symbols[] = $row["symbol"];
            }                    
            
            render("sell_display.php", ["symbols" => $symbols, "title" => "Sell"]);
        }
    }    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {    
        // opens share table
        $rows = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // declares variable
        $shares = $rows[0]["shares"];
        $value = lookup($_POST["symbol"]);
        
        // updates tables 
        query("START TRANSACTION");
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        query("UPDATE users SET cash = cash + ? WHERE id = ?", ($value["price"] * $shares), $_SESSION["id"]);
        history("SELL", $_POST["symbol"], $shares);
        query("COMMIT");
        // redirects to portfolio
        redirect("/");
    }
    
    
?>
