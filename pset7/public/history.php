<?php
    
    require("../includes/config.php");
    
    // open table
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    // sanity check
    if (empty($rows))
    {
        apologize("No record found.");
    }
    else
    {                      
        // fills array
        foreach ($rows as $row)
        {
            // Format date
            $timestamp = strtotime($row["date"]);
            $histories[] = [
                "transaction" => $row["transaction"],
                "date" => date("m/d/Y, g:i:sa O", $timestamp),
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => money_format("$%n", $row["price"])
                ];
            
        }     
        render("history_table.php", ["title" => "History", "histories" => $histories]);
    }   
?>
