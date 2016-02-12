<?php

    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    { 
        $stock = lookup($_POST["symbol"]);
        
        if ($stock === false)
        {
            apologize("Cannot find symbol \"" . $_POST["symbol"] . "\"");
        } 
        else
        {
            render("quote_display.php", ["title" => "Quote", "quote_symbol" => $stock["symbol"], "quote_name" => $stock["name"], "quote_price" => money_format("$%n", $stock["price"]) ]);
        }
    }    

?>
