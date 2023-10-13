const char PAGE_oli_scenarios[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h2>Oli Scenarios</h2>
  <form action="/submitConfig" method="post" target="_self">
    <fieldset>
    <legend>Maandag</legend>  
        <input type="time" id="tijdma1" name="tijdma1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurma1" name="kleurma1" value="#ff6600">
        <input type="number" id="intensiteitma1" name="intensiteitma1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdma2" name="tijdma2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurma2" name="kleurma2" value="#ffff66">
        <input type="number" id="intensiteitma2" name="intensiteitma2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdma3" name="tijdma3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurma3" name="kleurma3" value="#66ff66">
        <input type="number" id="intensiteitma3" name="intensiteitma3" value="50" min="1" max="100" style="width: 2.5em;">
        <br>
        <input type="time" id="tijdma4" name="tijdma4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>  
    <br>
    <fieldset>
    <legend>Dinsdag</legend>
        <button type="button" onclick="dinsdagAlsMaandag()">Copy from yesterday</button> <!-- type="button prevents the button from implicitly performing a submit -->
        <br>
        <input type="time" id="tijddi1" name="tijddi1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurdi1" name="kleurdi1" value="#ff6600">
        <input type="number" id="intensiteitdi1" name="intensiteitdi1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijddi2" name="tijddi2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurdi2" name="kleurdi2" value="#ffff66">
        <input type="number" id="intensiteitdi2" name="intensiteitdi2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijddi3" name="tijddi3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurdi3" name="kleurdi3" value="#66ff66">
        <input type="number" id="intensiteitdi3" name="intensiteitdi3" value="50" min="1" max="100" style="width: 2.5em;"> 
        <br>
        <input type="time" id="tijddi4" name="tijddi4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Woensdag</legend>
        <button type="button" onclick="woensdagAlsDinsdag()">Copy from yesterday</button>
        <br>    
        <input type="time" id="tijdwo1" name="tijdwo1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurwo1" name="kleurwo1" value="#ff6600">
        <input type="number" id="intensiteitwo1" name="intensiteitwo1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdwo2" name="tijdwo2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurwo2" name="kleurwo2" value="#ffff66">
        <input type="number" id="intensiteitwo2" name="intensiteitwo2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdwo3" name="tijdwo3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurwo3" name="kleurwo3" value="#66ff66">
        <input type="number" id="intensiteitwo3" name="intensiteitwo3" value="50" min="1" max="100" style="width: 2.5em;"> 
        <br>
        <input type="time" id="tijdwo4" name="tijdwo4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Donderdag</legend> 
        <button type="button" onclick="donderdagAlsWoensdag()">Copy from yesterday</button>
        <br>     
        <input type="time" id="tijddo1" name="tijddo1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurdo1" name="kleurdo1" value="#ff6600">
        <input type="number" id="intensiteitdo1" name="intensiteitdo1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijddo2" name="tijddo2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurdo2" name="kleurdo2" value="#ffff66">
        <input type="number" id="intensiteitdo2" name="intensiteitdo2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijddo3" name="tijddo3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurdo3" name="kleurdo3" value="#66ff66">
        <input type="number" id="intensiteitdo3" name="intensiteitdo3" value="50" min="1" max="100" style="width: 2.5em;">   
        <br>
        <input type="time" id="tijddo4" name="tijddo4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Vrijdag</legend>  
        <button type="button" onclick="vrijdagAlsdonderdag()">Copy from yesterday</button>
        <br>    
        <input type="time" id="tijdvr1" name="tijdvr1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurvr1" name="kleurvr1" value="#ff6600">
        <input type="number" id="intensiteitvr1" name="intensiteitvr1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdvr2" name="tijdvr2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurvr2" name="kleurvr2" value="#ffff66">
        <input type="number" id="intensiteitvr2" name="intensiteitvr2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdvr3" name="tijdvr3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurvr3" name="kleurvr3" value="#66ff66">
        <input type="number" id="intensiteitvr3" name="intensiteitvr3" value="50" min="1" max="100" style="width: 2.5em;"> 
        <br>
        <input type="time" id="tijdvr4" name="tijdvr4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Zaterdag</legend>  
        <button type="button" onclick="zaterdagAlsVrijdag()">Copy from yesterday</button>
        <br>    
        <input type="time" id="tijdza1" name="tijdza1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurza1" name="kleurza1" value="#ff6600">
        <input type="number" id="intensiteitza1" name="intensiteitza1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdza2" name="tijdza2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurza2" name="kleurza2" value="#ffff66">
        <input type="number" id="intensiteitza2" name="intensiteitza2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdza3" name="tijdza3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurza3" name="kleurza3" value="#66ff66">
        <input type="number" id="intensiteitza3" name="intensiteitza3" value="50" min="1" max="100" style="width: 2.5em;"> 
        <br>
        <input type="time" id="tijdza4" name="tijdza4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset> 
    <br>    
    <fieldset>
    <legend>Zondag</legend>  
        <button type="button" onclick="zondagAlszaterdag()">Copy from yesterday</button>
        <br>    
        <input type="time" id="tijdzo1" name="tijdzo1" value="06:32" style="width: 5em;">
        <input type="color" id="kleurzo1" name="kleurzo1" value="#ff6600">
        <input type="number" id="intensiteitzo1" name="intensiteitzo1" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdzo2" name="tijdzo2" value="07:00" style="width: 5em;">
        <input type="color" id="kleurzo2" name="kleurzo2" value="#ffff66">
        <input type="number" id="intensiteitzo2" name="intensiteitzo2" value="50" min="1" max="100" style="width: 2.5em;">        
        <br>
        <input type="time" id="tijdzo3" name="tijdzo3" value="07:15" style="width: 5em;">
        <input type="color" id="kleurzo3" name="kleurzo3" value="#66ff66">
        <input type="number" id="intensiteitzo3" name="intensiteitzo3" value="50" min="1" max="100" style="width: 2.5em;"> 
        <br>
        <input type="time" id="tijdzo4" name="tijdzo4" value="07:15" style="width: 5em;">
        <label>Uit</label>
    </fieldset>
    <br><br>    
    <input type="submit">      
    <br><br>
    <fieldset>
        <a href="/config">Oli config</a>
        <br>
        <a href="/status">Oli status</a>
    </fieldset>
  </form>
  <script>
  function dinsdagAlsMaandag() {
    document.getElementById("tijddi1").value = document.getElementById("tijdma1").value;
    document.getElementById("tijddi2").value = document.getElementById("tijdma2").value;
    document.getElementById("tijddi3").value = document.getElementById("tijdma3").value;
    document.getElementById("tijddi4").value = document.getElementById("tijdma4").value;
    document.getElementById("kleurdi1").value = document.getElementById("kleurma1").value;
    document.getElementById("kleurdi2").value = document.getElementById("kleurma2").value;
    document.getElementById("kleurdi3").value = document.getElementById("kleurma3").value;
    document.getElementById("intensiteitdi1").value = document.getElementById("intensiteitma1").value;
    document.getElementById("intensiteitdi2").value = document.getElementById("intensiteitma2").value;
    document.getElementById("intensiteitdi3").value = document.getElementById("intensiteitma3").value;
  }
  function woensdagAlsDinsdag() {
    document.getElementById("tijdwo1").value = document.getElementById("tijddi1").value;
    document.getElementById("tijdwo2").value = document.getElementById("tijddi2").value;
    document.getElementById("tijdwo3").value = document.getElementById("tijddi3").value;
    document.getElementById("tijdwo4").value = document.getElementById("tijddi4").value;
    document.getElementById("kleurwo1").value = document.getElementById("kleurdi1").value;
    document.getElementById("kleurwo2").value = document.getElementById("kleurdi2").value;
    document.getElementById("kleurwo3").value = document.getElementById("kleurdi3").value;
    document.getElementById("intensiteitwo1").value = document.getElementById("intensiteitdi1").value;
    document.getElementById("intensiteitwo2").value = document.getElementById("intensiteitdi2").value;
    document.getElementById("intensiteitwo3").value = document.getElementById("intensiteitdi3").value;
  }
  function donderdagAlsWoensdag() {
    document.getElementById("tijddo1").value = document.getElementById("tijdwo1").value;
    document.getElementById("tijddo2").value = document.getElementById("tijdwo2").value;
    document.getElementById("tijddo3").value = document.getElementById("tijdwo3").value;
    document.getElementById("tijddo4").value = document.getElementById("tijdwo4").value;
    document.getElementById("kleurdo1").value = document.getElementById("kleurwo1").value;
    document.getElementById("kleurdo2").value = document.getElementById("kleurwo2").value;
    document.getElementById("kleurdo3").value = document.getElementById("kleurwo3").value;
    document.getElementById("intensiteitdo1").value = document.getElementById("intensiteitwo1").value;
    document.getElementById("intensiteitdo2").value = document.getElementById("intensiteitwo2").value;
    document.getElementById("intensiteitdo3").value = document.getElementById("intensiteitwo3").value;
  }
  function vrijdagAlsDonderdag() {
    document.getElementById("tijdvr1").value = document.getElementById("tijddo1").value;
    document.getElementById("tijdvr2").value = document.getElementById("tijddo2").value;
    document.getElementById("tijdvr3").value = document.getElementById("tijddo3").value;
    document.getElementById("tijdvr4").value = document.getElementById("tijddo4").value;
    document.getElementById("kleurvr1").value = document.getElementById("kleurdo1").value;
    document.getElementById("kleurvr2").value = document.getElementById("kleurdo2").value;
    document.getElementById("kleurvr3").value = document.getElementById("kleurdo3").value;
    document.getElementById("intensiteitvr1").value = document.getElementById("intensiteitdo1").value;
    document.getElementById("intensiteitvr2").value = document.getElementById("intensiteitdo2").value;
    document.getElementById("intensiteitvr3").value = document.getElementById("intensiteitdo3").value;
  }
  function zaterdagAlsVrijdag() {
    document.getElementById("tijdza1").value = document.getElementById("tijdvr1").value;
    document.getElementById("tijdza2").value = document.getElementById("tijdvr2").value;
    document.getElementById("tijdza3").value = document.getElementById("tijdvr3").value;
    document.getElementById("tijdza4").value = document.getElementById("tijdvr4").value;
    document.getElementById("kleurza1").value = document.getElementById("kleurvr1").value;
    document.getElementById("kleurza2").value = document.getElementById("kleurvr2").value;
    document.getElementById("kleurza3").value = document.getElementById("kleurvr3").value;
    document.getElementById("intensiteitza1").value = document.getElementById("intensiteitvr1").value;
    document.getElementById("intensiteitza2").value = document.getElementById("intensiteitvr2").value;
    document.getElementById("intensiteitza3").value = document.getElementById("intensiteitvr3").value;
  }
  function zondagAlsZaterdag() {
    document.getElementById("tijdzo1").value = document.getElementById("tijdza1").value;
    document.getElementById("tijdzo2").value = document.getElementById("tijdza2").value;
    document.getElementById("tijdzo3").value = document.getElementById("tijdza3").value;
    document.getElementById("tijdzo4").value = document.getElementById("tijdza4").value;
    document.getElementById("kleurzo1").value = document.getElementById("kleurza1").value;
    document.getElementById("kleurzo2").value = document.getElementById("kleurza2").value;
    document.getElementById("kleurzo3").value = document.getElementById("kleurza3").value;
    document.getElementById("intensiteitzo1").value = document.getElementById("intensiteitza1").value;
    document.getElementById("intensiteitzo2").value = document.getElementById("intensiteitza2").value;
    document.getElementById("intensiteitzo3").value = document.getElementById("intensiteitza3").value;
  }  
</script>  
</body>
</html>
)=====";
