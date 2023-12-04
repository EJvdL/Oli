const char PAGE_oli_scenarios[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h2>Oli Scenarios</h2>
  <form action="/submitScenario" method="post" target="_self">
    <fieldset>
    <legend>Maandag</legend> 
        <button type="button" onclick="maandagAlsZondag()">Kopieer van zondag</button> <!-- type="button prevents the button from implicitly performing a submit -->
        <br>
        <input type="time" required id="T10" name="T10" value="%T10%" style="width: 5em;">
        <input type="color" required id="K10" name="K10" value="%K10%"> 
        <br>
        <input type="time" required id="T11" name="T11" value="%T11%" style="width: 5em;">
        <input type="color" required id="K11" name="K11" value="%K11%">
        <br>
        <input type="time" required id="T12" name="T12" value="%T12%" style="width: 5em;">
        <input type="color" required id="K12" name="K12" value="%K12%">
        <br>
        <input type="time" required id="T13" name="T13" value="%T13%" style="width: 5em;">
        <input type="color" required id="K13" name="K13" value="%K13%">
    </fieldset>  
    <br>
    <fieldset>
    <legend>Dinsdag</legend>
        <button type="button" onclick="dinsdagAlsMaandag()">Kopieer van maandag</button> <!-- type="button prevents the button from implicitly performing a submit -->
        <br>
        <input type="time" required id="T20" name="T20" value="%T20%" style="width: 5em;">
        <input type="color" required id="K20" name="K20" value="%K20%">
        <br>
        <input type="time" required id="T21" name="T21" value="%T21%" style="width: 5em;">
        <input type="color" required id="K21" name="K21" value="%K21%">
        <br>
        <input type="time" required id="T22" name="T22" value="%T22%" style="width: 5em;">
        <input type="color" required id="K22" name="K22" value="%K22%">
        <br>
        <input type="time" required id="T23" name="T23" value="%T23%" style="width: 5em;">
        <input type="color" required id="K23" name="K23" value="%K23%">
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Woensdag</legend>
        <button type="button" onclick="woensdagAlsDinsdag()">Kopieer van dinsdag</button>
        <br>    
        <input type="time" required id="T30" name="T30" value="%T30%" style="width: 5em;">
        <input type="color" required id="K30" name="K30" value="%K30%">
        <br>
        <input type="time" required id="T31" name="T31" value="%T31%" style="width: 5em;">
        <input type="color" required id="K31" name="K31" value="%K31%">
        <br>
        <input type="time" required id="T32" name="T32" value="%T32%" style="width: 5em;">
        <input type="color" required id="K32" name="K32" value="%K32%">
        <br>
        <input type="time" required id="T33" name="T33" value="%T33%" style="width: 5em;">
        <input type="color" required id="K33" name="K33" value="%K33%">
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Donderdag</legend> 
        <button type="button" onclick="donderdagAlsWoensdag()">Kopieer van woensdag</button>
        <br>     
        <input type="time" required id="T40" name="T40" value="%T40%" style="width: 5em;">
        <input type="color" required id="K40" name="K40" value="%K40%">
        <br>
        <input type="time" required id="T41" name="T41" value="%T41%" style="width: 5em;">
        <input type="color" required id="K41" name="K41" value="%K41%">
        <br>
        <input type="time" required id="T42" name="T42" value="%T42%" style="width: 5em;">
        <input type="color" required id="K42" name="K42" value="%K42%">
        <br>
        <input type="time" required id="T43" name="T43" value="%T43%" style="width: 5em;">
        <input type="color" required id="K43" name="K43" value="%K43%">
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Vrijdag</legend>  
        <button type="button" onclick="vrijdagAlsDonderdag()">Kopieer van donderdag</button>
        <br>    
        <input type="time" required id="T50" name="T50" value="%T50%" style="width: 5em;">
        <input type="color" required id="K50" name="K50" value="%K50%">
        <br>
        <input type="time" required id="T51" name="T51" value="%T51%" style="width: 5em;">
        <input type="color" required id="K51" name="K51" value="%K51%">
        <br>
        <input type="time" required id="T52" name="T52" value="%T52%" style="width: 5em;">
        <input type="color" required id="K52" name="K52" value="%K52%">
        <br>
        <input type="time" required id="T53" name="T53" value="%T53%" style="width: 5em;">
        <input type="color" required id="K53" name="K53" value="%K53%">
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Zaterdag</legend>  
        <button type="button" onclick="zaterdagAlsVrijdag()">Kopieer van vrijdag</button>
        <br>    
        <input type="time" required id="T60" name="T60" value="%T60%" style="width: 5em;">
        <input type="color" required id="K60" name="K60" value="%K60%">
        <br>
        <input type="time" required id="T61" name="T61" value="%T61%" style="width: 5em;">
        <input type="color" required id="K61" name="K61" value="%K61%">
        <br>
        <input type="time" required id="T62" name="T62" value="%T62%" style="width: 5em;">
        <input type="color" required id="K62" name="K62" value="%K62%">
        <br>
        <input type="time" required id="T63" name="T63" value="%T63%" style="width: 5em;">
        <input type="color" required id="K63" name="K63" value="%K63%">
    </fieldset> 
    <br>    
    <fieldset>
    <legend>Zondag</legend>  
        <button type="button" onclick="zondagAlsZaterdag()">Kopieer van zaterdag</button>
        <br>
        <input type="time" required id="T00" name="T00" value="%T00%" style="width: 5em;">
        <input type="color" required id="K00" name="K00" value="%K00%">
        <br>
        <input type="time" required id="T01" name="T01" value="%T01%" style="width: 5em;">
        <input type="color" required id="K01" name="K01" value="%K01%">
        <br>
        <input type="time" required id="T02" name="T02" value="%T02%" style="width: 5em;">
        <input type="color" required id="K02" name="K02" value="%K02%">
        <br>
        <input type="time" required id="T03" name="T03" value="%T03%" style="width: 5em;">
        <input type="color" required id="K03" name="K03" value="%K03%">
    </fieldset>
    <br><br>    
    <input type="submit">      
    <br><br>
    <fieldset>
        <a href="/config">Oli config</a>
        <br>
        <a href="/status">Oli status</a>
        <br>
        <a href="/colorPicker">Oli Kleuren tester</a>           
    </fieldset>
  </form>
  <script>
  function maandagAlsZondag() {
    document.getElementById("T10").value = document.getElementById("T00").value;
    document.getElementById("T11").value = document.getElementById("T01").value;
    document.getElementById("T12").value = document.getElementById("T02").value;
    document.getElementById("T13").value = document.getElementById("T03").value;
    document.getElementById("K10").value = document.getElementById("K00").value;
    document.getElementById("K11").value = document.getElementById("K01").value;
    document.getElementById("K12").value = document.getElementById("K02").value;
    document.getElementById("K13").value = document.getElementById("K03").value;
  }  
  function dinsdagAlsMaandag() {
    document.getElementById("T20").value = document.getElementById("T10").value;
    document.getElementById("T21").value = document.getElementById("T11").value;
    document.getElementById("T22").value = document.getElementById("T12").value;
    document.getElementById("T23").value = document.getElementById("T13").value;
    document.getElementById("K20").value = document.getElementById("K10").value;
    document.getElementById("K21").value = document.getElementById("K11").value;
    document.getElementById("K22").value = document.getElementById("K12").value;
    document.getElementById("K23").value = document.getElementById("K13").value;
  }
  function woensdagAlsDinsdag() {
    document.getElementById("T30").value = document.getElementById("T20").value;
    document.getElementById("T31").value = document.getElementById("T21").value;
    document.getElementById("T32").value = document.getElementById("T22").value;
    document.getElementById("T33").value = document.getElementById("T23").value;
    document.getElementById("K30").value = document.getElementById("K20").value;
    document.getElementById("K31").value = document.getElementById("K21").value;
    document.getElementById("K32").value = document.getElementById("K22").value;
    document.getElementById("K33").value = document.getElementById("K23").value;
  }
  function donderdagAlsWoensdag() {
    document.getElementById("T40").value = document.getElementById("T30").value;
    document.getElementById("T41").value = document.getElementById("T31").value;
    document.getElementById("T42").value = document.getElementById("T32").value;
    document.getElementById("T43").value = document.getElementById("T33").value;
    document.getElementById("K40").value = document.getElementById("K30").value;
    document.getElementById("K41").value = document.getElementById("K31").value;
    document.getElementById("K42").value = document.getElementById("K32").value;
    document.getElementById("K43").value = document.getElementById("K33").value;
  }
  function vrijdagAlsDonderdag() {
    document.getElementById("T50").value = document.getElementById("T40").value;
    document.getElementById("T51").value = document.getElementById("T41").value;
    document.getElementById("T52").value = document.getElementById("T42").value;
    document.getElementById("T53").value = document.getElementById("T43").value;
    document.getElementById("K50").value = document.getElementById("K40").value;
    document.getElementById("K51").value = document.getElementById("K41").value;
    document.getElementById("K52").value = document.getElementById("K42").value;
    document.getElementById("K53").value = document.getElementById("K43").value;
  }
  function zaterdagAlsVrijdag() {
    document.getElementById("T60").value = document.getElementById("T50").value;
    document.getElementById("T61").value = document.getElementById("T51").value;
    document.getElementById("T62").value = document.getElementById("T52").value;
    document.getElementById("T63").value = document.getElementById("T53").value;
    document.getElementById("K60").value = document.getElementById("K50").value;
    document.getElementById("K61").value = document.getElementById("K51").value;
    document.getElementById("K62").value = document.getElementById("K52").value;
    document.getElementById("K63").value = document.getElementById("K53").value;
  }
  function zondagAlsZaterdag() {
    document.getElementById("T00").value = document.getElementById("T60").value;
    document.getElementById("T01").value = document.getElementById("T61").value;
    document.getElementById("T02").value = document.getElementById("T62").value;
    document.getElementById("T03").value = document.getElementById("T63").value;
    document.getElementById("K00").value = document.getElementById("K60").value;
    document.getElementById("K01").value = document.getElementById("K61").value;
    document.getElementById("K02").value = document.getElementById("K62").value;
    document.getElementById("K03").value = document.getElementById("K63").value;
  }  
</script>  
</body>
</html>
)=====";
