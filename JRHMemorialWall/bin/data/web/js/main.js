var socket;

var messageDiv;
var statusDiv;
var button;
var textField;
var lightsCheckbox, soundCheckbox;
var socketOpen = false;;

$(document).ready( function() {


	lightsCheckbox = document.getElementById("lightsCheckbox");
	soundCheckbox = document.getElementById("soundCheckbox");

	setupSocket();
	
	document.getElementById("brow").textContent = " " + BrowserDetect.browser + " "
		+ BrowserDetect.version +" " + BrowserDetect.OS +" ";

	messageDiv = document.getElementById("messages");
	statusDiv = document.getElementById("status");

	
	lightsCheckbox.onclick = function(e){
		//pingSocket();
		//check state
		if(lightsCheckbox.checked){
			//socket.send("ON");
			pingSocket("ON");
		}
		else{
			//socket.send("OFF");
			pingSocket("OFF");
		}
	}

	soundCheckbox.onclick = function(e){
		//pingSocket();
		//check state
		if(soundCheckbox.checked){
			//socket.send("UNMUTE");
			pingSocket("UNMUTE");
		}
		else{
			//socket.send("MUTE");
			pingSocket("MUTE");
		}
	}

	
});

function pingSocket(message){
	if(!socketOpen){
		//open socket, then send message
		setupSocket(message);
		//socket.open();
	}
	else{
		//send message
		socket.send(message);
	}
}

// send value from text input
function sendMessageForm(){
	socket.send(message.value);
	message.value = "";
}

// setup web socket
function setupSocket(message){

	// setup websocket
	// get_appropriate_ws_url is a nifty function by the libwebsockets people
	// it decides what the websocket url is based on the broswer url
	// e.g. https://mygreathost:9099 = wss://mygreathost:9099

	/*if (BrowserDetect.browser == "Firefox") {
		socket = new MozWebSocket(get_appropriate_ws_url());
	} else {*/
		socket = new WebSocket(get_appropriate_ws_url());
	//}
	
	// open
	try {
		socket.onopen = function() {
			statusDiv.style.backgroundColor = "#40ff40";
			statusDiv.textContent = "connection open";
			socketOpen = true;
			//send message if there is one
			if(message){
				socket.send(message);
			}
		} 

		// received message
		socket.onmessage =function got_packet(msg) {
			//messageDiv.innerHTML = msg.data + "<br />" + messageDiv.innerHTML;
			console.log(msg.data);
			if(msg.data == "ON"){
				lightsCheckbox.checked = true;
			}
			else if(msg.data == "OFF"){
				lightsCheckbox.checked = false;
			}
			else if(msg.data == "MUTE"){
				soundCheckbox.checked = false;
			}
			else if(msg.data == "UNMUTE"){
				soundCheckbox.checked = true;
			}
		}

		socket.onclose = function(){
			statusDiv.style.backgroundColor = "#ff4040";
			statusDiv.textContent = " connection closed ";
			socketOpen = false;
		}
		
	} catch(exception) {
		alert('<p>Error' + exception);  
	}
}