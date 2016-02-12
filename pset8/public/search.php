<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    $data = [];
     
    // checks arg NOT is numeric
    if (!ctype_digit($_GET["geo"])) 
    {
        
        // presume non alphanumeric is delimiter
        $_GET["geo"] = preg_replace("/[^a-zA-ZÀ-ÿ0-9-+ ]/", ",", $_GET["geo"]);
        
        // put args in array
        $data = explode(",", $_GET["geo"]);

        // add % for SQL LIKE
        foreach($data as $key => $value)
        {
            $data[$key] = trim($data[$key], " ");
            $data[$key] .= "%";
        }
        
        // get data
        switch(count($data))
        {
            case 1:
                $places = query("SELECT * FROM places WHERE place_name LIKE ? OR admin_name1 LIKE ? LIMIT 10", $data[0], $data[0]);
                break;
                
            case 2:
                $places = query("SELECT * FROM places WHERE place_name LIKE ? AND (admin_name1 LIKE ? OR admin_code1 = ? LIMIT 10)", $data[0], $data[1] . "%", $data[1]);
                break;
                
            default:
                $places = query("SELECT * FROM places WHERE place_name LIKE ? AND admin_name1 LIKE ? AND country_code = ? LIMIT 10", $data[0], $data[1], $data[2]);
                break;
        }       
    }
    else
    {
        $data = $_GET["geo"];
        
        // if no full zip code
        if(!isset($data[4]))
        {
            // concat % for LIKE
            $data .= "%";
        }

        $places = query("SELECT * FROM places WHERE postal_code LIKE ? LIMIT 10", $data);
    }
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
