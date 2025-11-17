<?php
$cookieName = "my_Cookie";
$cookieValue = "Example_cookie_value";
$expirationTime = time() + 3600;
$secureOnly = true;
setcookie($cookieName, $cookieValue, $expirationTime, "/", "", $secureOnly, true);
echo "Secure cookie named 'my_Cookie' has been set.";
?>
