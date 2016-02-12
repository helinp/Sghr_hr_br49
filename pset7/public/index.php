<?php

    // configuration
    require("../includes/config.php"); 

    // open table portfolio
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    // NULL CHECK
    if (empty($rows))
    {
         $positions[] = [
                "symbol" => NULL,
                "name" => NULL,
                "price" => NULL,
                "shares" => NULL,
                "total" => NULL];      
    }    
    else
    {
        // fills array for portfolio
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "symbol" => $row["symbol"],
                    "name" => $stock["name"],
                    "price" => money_format("$%n", $stock["price"]),
                    "shares" => $row["shares"],
                    "total" => money_format("$%n", $stock["price"] * $row["shares"])];
            }
        }
    }
    
    // fills variables
    $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = money_format("$%n", $rows[0]["cash"]);
   
    // render portfolio
    render("portfolio.php", ["cash" => $cash, "positions" => $positions, "title" => "Portfolio"] );
?>
