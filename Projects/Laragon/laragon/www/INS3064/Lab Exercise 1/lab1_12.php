<?php
session_save_path('i:/custom/');
$sessionSavePath = session_save_path(); $sessionFiles = glob($sessionSavePath . '/*');
$activeSessions = 0;
foreach ($sessionFiles as $sessionFile) if (is_file($sessionFile) && filectime($sessionFile) + ini_get('session.gc_maxlifetime') > time()) $activeSessions++;                   
echo "Number of active sessions: " . $activeSessions;
?>
