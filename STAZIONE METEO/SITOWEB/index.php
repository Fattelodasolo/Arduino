<body>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Stazione Meteo - Reshitoze</title>
</head>
<h1 align="center"><font size="90"><strong>STAZIONE METEO - FARO SUPERIORE (ME) - 116,24m S.L.M.</strong></font></h1>
  <h2 align="center"><font><strong>created by Reshitoze</strong></font></h2>
</body>

<?php
// effettuo la connessione al mysql
$host = "www.misito.it";
$database = "my_database";
$user = "nomeutente";
$password = "";
$tabella = "mytabella";
$link = mysqli_connect ($host, $user, $password);
if (!$link) {
die('Non connesso: ' . mysqli_error());	
}
// effettuo la connessione al database mysql
$db_selected = mysqli_select_db ($link, $database);
if (!$db_selected) {
die ('Non &egrave; possibile connettersi al database: ' .mysqli_error());
};
?>


<p align="center">
<table width="1039" height="69" border="1" bgcolor="silver">
<tr>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Data:</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Temperatura (°C):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Umidit&agrave; (%): </strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Luminosit&agrave; (%): </strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Pressione (Pa):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Pioggia (mm/h):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Altezza della neve (cm):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Monossido di Carbonio (ppm):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Vento (Km/h):</strong></font></div></td>
<td width="180" bgcolor="black"><div align="center"><font color="white"><strong>Punto di rugiada (°C):</strong></font></div></td>

<?php
$query = mysqli_query($link, "SELECT * from $tabella");
while($row = mysqli_fetch_array($query))
{
echo "<tr><td><strong>" .$time_stamp = $row ['time_stamp']."</strong></td>";
echo "<td><strong>" .$temperatura = $row['temperatura']."</strong></td>";
echo "<td><strong>" .$umidita = $row ['umidita']."</strong></td>";
echo "<td><strong>" .$luminosita = $row ['luminosita']."</strong></td>";
echo "<td><strong>" .$pressione = $row ['pressione']."</strong></td>";
echo "<td><strong>" .$pioggia = $row ['pioggia']."</strong></td>";
echo "<td><strong>" .$neve = $row ['neve']."</strong></td>";
echo "<td><strong>" .$monossido = $row ['monossido']."</strong></td>";
echo "<td><strong>" .$vento = $row ['vento']."</strong></td>";
echo "<td><strong>" .$rugiada = $row ['rugiada']."</strong></td></tr>";
}
?>
</tr>
</table>
</p>
