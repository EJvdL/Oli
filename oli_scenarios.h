const char PAGE_oli_scenarios[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<h2>Oli Scenarios</h2>
    <fieldset>
    <legend>Maandag</legend>  
        <label for="tijdma1">Tijd 1</label>
        <input type="time" id="tijdma1" name="tijdma1" value="06:32">
        <input type="color" id="kleurma1" name="kleurma1" value="#ff6600">
        <input type="int" id="intensiteitma1" name="intensiteitma1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijdma2" name="tijdma2" value="07:00">
        <input type="color" id="kleurma2" name="kleurma2" value="#ffff66">
        <input type="int" id="intensiteitma2" name="intensiteitma2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijdma3" name="tijdma3" value="07:15">
        <input type="color" id="kleurma3" name="kleurma3" value="#66ff66">
        <input type="int" id="intensiteitma3" name="intensiteitma3" value="50">        
    </fieldset>  
    <br>
    <fieldset>
    <legend>Dinsdag</legend>  
        <label for="tijddi1">Tijd 1</label>
        <input type="time" id="tijddi1" name="tijddi1" value="06:32">
        <input type="color" id="kleurdi1" name="kleurdi1" value="#ff6600">
        <input type="int" id="intensiteitdi1" name="intensiteitdi1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijddi2" name="tijddi2" value="07:00">
        <input type="color" id="kleurdi2" name="kleurdi2" value="#ffff66">
        <input type="int" id="intensiteitdi2" name="intensiteitdi2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijddi3" name="tijddi3" value="07:15">
        <input type="color" id="kleurdi3" name="kleurdi3" value="#66ff66">
        <input type="int" id="intensiteitdi3" name="intensiteitdi3" value="50"> 
    </fieldset>  
    <br>    
    <fieldset>
        <label for="tijdwo1">Tijd 1</label>
        <input type="time" id="tijdwo1" name="tijdwo1" value="06:32">
        <input type="color" id="kleurwo1" name="kleurwo1" value="#ff6600">
        <input type="int" id="intensiteitwo1" name="intensiteitwo1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijdwo2" name="tijdwo2" value="07:00">
        <input type="color" id="kleurwo2" name="kleurwo2" value="#ffff66">
        <input type="int" id="intensiteitwo2" name="intensiteitwo2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijdwo3" name="tijdwo3" value="07:15">
        <input type="color" id="kleurwo3" name="kleurwo3" value="#66ff66">
        <input type="int" id="intensiteitwo3" name="intensiteitwo3" value="50"> 
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Donderdag</legend>  
        <label for="tijddo1">Tijd 1</label>
        <input type="time" id="tijddo1" name="tijddo1" value="06:32">
        <input type="color" id="kleurdo1" name="kleurdo1" value="#ff6600">
        <input type="int" id="intensiteitdo1" name="intensiteitdo1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijddo2" name="tijddo2" value="07:00">
        <input type="color" id="kleurdo2" name="kleurdo2" value="#ffff66">
        <input type="int" id="intensiteitdo2" name="intensiteitdo2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijddo3" name="tijddo3" value="07:15">
        <input type="color" id="kleurdo3" name="kleurdo3" value="#66ff66">
        <input type="int" id="intensiteitdo3" name="intensiteitdo3" value="50">   
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Vrijdag</legend>  
        <label for="tijdvr1">Tijd 1</label>
        <input type="time" id="tijdvr1" name="tijdvr1" value="06:32">
        <input type="color" id="kleurvr1" name="kleurvr1" value="#ff6600">
        <input type="int" id="intensiteitvr1" name="intensiteitvr1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijdvr2" name="tijdvr2" value="07:00">
        <input type="color" id="kleurvr2" name="kleurvr2" value="#ffff66">
        <input type="int" id="intensiteitvr2" name="intensiteitvr2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijdvr3" name="tijdvr3" value="07:15">
        <input type="color" id="kleurvr3" name="kleurvr3" value="#66ff66">
        <input type="int" id="intensiteitvr3" name="intensiteitvr3" value="50"> 
    </fieldset>  
    <br>    
    <fieldset>
    <legend>Zaterdag</legend>  
        <label for="tijdza1">Tijd 1</label>
        <input type="time" id="tijdza1" name="tijdza1" value="06:32">
        <input type="color" id="kleurza1" name="kleurza1" value="#ff6600">
        <input type="int" id="intensiteitza1" name="intensiteitza1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijdza2" name="tijdza2" value="07:00">
        <input type="color" id="kleurza2" name="kleurza2" value="#ffff66">
        <input type="int" id="intensiteitza2" name="intensiteitza2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijdza3" name="tijdza3" value="07:15">
        <input type="color" id="kleurza3" name="kleurza3" value="#66ff66">
        <input type="int" id="intensiteitza3" name="intensiteitza3" value="50"> 
    </fieldset> 
    <br>    
    <fieldset>
    <legend>Zondag</legend>  
        <label for="tijdzo1">Tijd 1</label>
        <input type="time" id="tijdzo1" name="tijdzo1" value="06:32">
        <input type="color" id="kleurzo1" name="kleurzo1" value="#ff6600">
        <input type="int" id="intensiteitzo1" name="intensiteitzo1" value="50">        
        <br>
        <label for="tijdma1">Tijd 2</label>
        <input type="time" id="tijdzo2" name="tijdzo2" value="07:00">
        <input type="color" id="kleurzo2" name="kleurzo2" value="#ffff66">
        <input type="int" id="intensiteitzo2" name="intensiteitzo2" value="50">        
        <br>
        <label for="tijdma3">Tijd 3</label>
        <input type="time" id="tijdzo3" name="tijdzo3" value="07:15">
        <input type="color" id="kleurzo3" name="kleurzo3" value="#66ff66">
        <input type="int" id="intensiteitzo3" name="intensiteitzo3" value="50"> 
    </fieldset>
    <br><br>    
    <input type="submit">      
    <br>
    <fieldset>
        <a href="/config">Oli config</a>
        <br>
        <a href="/status">Oli status</a>
    </fieldset>
</body>
</html>
)=====";
