let websocket = null;

///////////////////////////////////////////////////////////////////////////////
// PLATFORM ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let pf = navigator.platform;
let useTouchEvents = (pf == "iPhone" || pf == "iPad" || pf == "Android");
let useMouseEvents = (pf == "Win32" || !useTouchEvents);


///////////////////////////////////////////////////////////////////////////////
// FOR CONNECTION /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let pcIpAdressElt = document.querySelector("#pcIpAdress");
let origin = window.location.origin;
if (pcIpAdressElt.value.length == 0) {
	pcIpAdressElt.value = (origin != null && origin != "null" ? origin : "");
}
let wsPortElt = document.querySelector("#wsPort");
let connectionWidget = document.querySelector(".connection-widget");
let hazeElt = document.querySelector(".haze");

document.querySelector("form").addEventListener("submit", function (e) {
	e.preventDefault();

	let pcIpAdress = pcIpAdressElt.value;
	let wsPort = wsPortElt.value;
	if (pcIpAdress.length == 0 || wsPort.length == 0 || isNaN(Number(wsPort))) {
		console.log("stopped");
		return;
	}

	let wsUrl = `ws://${pcIpAdress}:${wsPort}`;
	websocket = new WebSocket(wsUrl);

	websocket.addEventListener("open", function() {
		console.log("OPEN");
		connectionWidget.classList.add("connected");
		if (hazeElt != null) hazeElt.classList.add("connected");
	});

	websocket.addEventListener("message", function(e) {
		console.log("MESSAGE: " + e.data);
	});

	websocket.addEventListener("error", function(e) {
		console.log("WS_ERROR: " + e.data);
	});

	websocket.addEventListener("close", function() {
		console.log("CLOSE");
		connectionWidget.classList.remove("connected");
		if (hazeElt != null) hazeElt.classList.remove("connected");
	});
});


///////////////////////////////////////////////////////////////////////////////
// UJPS ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let sendButtonMouse = (iButton,bPressed) => {
	// if (!useMouseEvents) return;
	if (websocket == null) return;
	let text = "button/" + iButton + "/" + bPressed;
	websocket.send(text);
	console.log(text);
};

let sendButtonTouch = (iButton,bPressed) => {
	// if (!useTouchEvents) return;
	if (websocket == null) return;
	let text = "button/" + iButton + "/" + bPressed;
	websocket.send(text);
	console.log(text);
};

let sendAxis = (iAxis,value) => {
	if (websocket == null) return;
	let text = "axis/" + iAxis + "/" + value;
	websocket.send(text);
	console.log(text);
};

let sendPov = (iPov,value) => {
	if (websocket == null) return;
	let text = "pov/" + "/" + iPov + "/" + value;
	websocket.send(text);
	console.log(text);
};

// // initialisation of buttons and axes
{
	let ujpsButtons = document.querySelectorAll("button[data-type=button][data-number]");
	for (let ujpsButton of ujpsButtons) {
		let dataNumber = parseInt(ujpsButton.getAttribute("data-number"));
		if (!isNaN(dataNumber)) {
			ujpsButton.addEventListener("mousedown", function() {
				sendButtonMouse(dataNumber,true);
			});
			ujpsButton.addEventListener("mouseup", function() {
				sendButtonMouse(dataNumber,false);
			});
			ujpsButton.addEventListener("touchstart", function() {
				sendButtonTouch(dataNumber,true);
			});
			ujpsButton.addEventListener("touchend", function() {
				sendButtonTouch(dataNumber,false);
			});
		}
	}

	let ujpsAxes = document.querySelectorAll("input[type=range][data-type=axis][data-number]");
	for (let ujpsAxis of ujpsAxes) {
		let dataNumber = parseInt(ujpsAxis.getAttribute("data-number"));
		if (!isNaN(dataNumber)) {
			ujpsAxis.addEventListener("input", function() {
				let f = 0.001 * ujpsAxis.value - 1.0;
				sendAxis(dataNumber,f);
			});

			ujpsAxis.setAttribute("min",0);
			ujpsAxis.setAttribute("max",2000);
			ujpsAxis.setAttribute("value",1000);
			sendAxis(dataNumber,0);
		}
	}
}

