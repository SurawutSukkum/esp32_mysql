<?php
$host = "localhost";
$db = "u909844480_testMesh";
$user = "u909844480_testMesh";
$pass = "uXjNx9@I";

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$val = $_GET['node'];
$val1 = $_GET['Temp'];
$val2 = $_GET['Humi'];
$val3 = $_GET['Pressure'];
$val4 = $_GET['Led'];
$sql = "INSERT INTO mesh_dataV1 (node,Temp,Humi,Pressure,Led) VALUES ($val,$val1,$val2,$val3,$val4);";

if ($conn->query($sql) === TRUE) {
    echo "save OK2";
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
