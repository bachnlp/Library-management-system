<?php
session_save_path('D:Projects/Laragon/laragon/custom/'); session_start();
if (isset ($_SESSION ["preferences"])) 
{
$userPreferences = $_SESSION["preferences"]; echo "User preferences: </br>";
foreach ($userPreferences as $key => $value) echo $key . ": " . $value . "</br>";
} else echo "No user preferences found."; ?>

