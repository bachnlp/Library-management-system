<?php
session_save_path('D:Projects/Laragon/laragon/custom/'); session_start();
if (isset($_SESSION['last_access_time'])) {
    $lastAccessTime = $_SESSION['last_access_time'];
    echo "Last access time: " . date('Y-m-d H:i:s', $lastAccessTime);
    $_SESSION['last_access_time'] = time(); 
} else {
    $_SESSION['last_access_time'] = time();
    echo "Session started. First access.";
}
?>
