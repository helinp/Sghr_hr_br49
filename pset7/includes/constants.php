<?php

    /**
     * constants.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Global constants.
     */

    // your database's name
    define("DATABASE", "pset7");

    // your database's password
    define("PASSWORD", "crimson");

    // your database's server
    define("SERVER", "localhost");

    // your database's username
    define("USERNAME", "jharvard");
    
    // absolute address
    define("FULL_URL", "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]");
    // No reply mail 
    define("NO_REPLY_MAIL", "no-reply@yopmail.com");
    
    // SMTP server: Use your ISP's SMTP server (e.g., smtp.fas.harvard.edu if on campus or smtp.comcast.net if off campus and your ISP is Comcast)
    define("SMTP_SERVER", "smtp.scarlet.be");
    

?>
