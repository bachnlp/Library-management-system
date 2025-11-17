<?php
session_save_path('D:/Projects/Laragon/laragon/custom/');
session_start();
$userPreferences = array (
"theme" => "light", "language" => "Spanish", "notifications" => true);
$_SESSION["preferences"] = $userPreferences;
echo "User preferences have been stored in the session variable 'preferences'."; ?>
