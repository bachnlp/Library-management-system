<?php
session_save_path('D:/Projects/Laragon/laragon/custom/');
session_start();
$_SESSION = [];
session_destroy();
echo "Session destroyed. All the session variables has been unset.";
?>
