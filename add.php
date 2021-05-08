<?php
$temp = $_GET['temp'];
$humi = $_GET['humi'];

$servername = "localhost:3307";
$username = "root";
$password = "";
$dbname = "monitor";

// Create connection
$conn = new mysqli($servername, $username,$password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$val = $_GET['temp'];
$val1 = $_GET['humi'];
$sql = "INSERT INTO esp32(Temp,humi) VALUES ($val,$val1);";




if ($conn->query($sql) === TRUE) {
    echo "save OK2";
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
