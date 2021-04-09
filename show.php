<html>
<head>
<meta http-equiv="refresh" content="3">
</head> 
<body>
<?php
$servername = "localhost:3307";
$username = "root";
$password = "surawut";
$dbname = "monitor";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM esp32 ORDER by No DESC LIMIT 20";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	echo "<table border='1'><th>ID</th><th>TEMP</th><th>HUMI</th><th>DATETIME</th>";
    while($row = $result->fetch_assoc()) {
		echo "<tr>";
		echo "<td>".$row['No']."</td>";
		echo "<td>".$row['Temp']."</td>";
		echo "<td>".$row['Humi']."</td>";
		echo "<td>".$row['date']."</td>";
		echo "</tr>";
    }
	echo "</table>";
} else {
    echo "0 results";
}
$conn->close();
?>
</body>
</html>