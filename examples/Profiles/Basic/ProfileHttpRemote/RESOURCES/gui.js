///////////////////////////////////////////////////////////////////////////////
// INIT AND CONSTANTS /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let target = "192.168.1.40:8080"; // to provide from an input inside html?
let msgDisplay = document.getElementById("msgDisplay");
let name = document.getElementById("name").innerHTML;
let iError = 0;
let sendRequest = true;


///////////////////////////////////////////////////////////////////////////////
// PLATFORM ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let pf = navigator.platform;
let useTouchEvents = (pf == "iPhone");
let useMouseEvents = (pf == "Win32" || !useTouchEvents);
msgDisplay.innerHTML = pf;


///////////////////////////////////////////////////////////////////////////////
// TESTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
document.fullscreenEnabled = true;
let body = document.getElementById("body");

body.onfullscreenerror = function() {
	msgDisplay.innerHTML = "full screen error";
}

window.onorientationchange = function(event) {
	//msgDisplay.innerHTML = "Orientation is now " + event.target.screen.orientation.angle;
	msgDisplay.innerHTML = "orientation changed";
}

let requestFullScreen = () => {
	body.requestFullscreen();
	msgDisplay.innerHTML = "full screen request";
};


///////////////////////////////////////////////////////////////////////////////
// SLIDERS LABELS /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let slider1 = document.getElementById("slider1");
let slabel1 = document.getElementById("slabel1");
slabel1.innerHTML = 0;
slider1.oninput = function() {
	let f = 0.001 * this.value - 1.0;
	slabel1.innerHTML = f.toString().substring(0,f<0?6:5);
};

let slider2 = document.getElementById("slider2");
let slabel2 = document.getElementById("slabel2");
slabel2.innerHTML = 0;
slider2.oninput = function() {
	let f = 0.001 * this.value - 1.0;
	slabel2.innerHTML = f.toString().substring(0,f<0?6:5);
};


///////////////////////////////////////////////////////////////////////////////
// UJPS ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let sendButtonMouse = (i,b) => {
	if (!useMouseEvents) return;
	let url = "http://" + target + "/button/" + name + "/" + i + "/" + (b ? "1" : "0");
	if (sendRequest) {
		let reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
};

let sendButtonTouch = (i,b) => {
	if (!useTouchEvents) return;
	let url = "http://" + target + "/button/" + name + "/" + i + "/" + (b ? "1" : "0");
	if (sendRequest) {
		let reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
};

let sendAxis = (i,f) => {
	let url = "http://" + target + "/axis/" + name + "/" + i + "/" + f;
	if (sendRequest) {
		let reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
};

let sendPov = (i,f) => {
	let url = "http://" + target + "/pov/" + name + "/" + i + "/" + f;
	if (sendRequest) {
		let reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
};

// initialisation
(function() {
	let ujpsButtons = document.querySelectorAll("button[data-type=button]");
	for (let ujpsButton of ujpsButtons) {
		if (ujpsButton.hasAttribute("data-number")) {
			let number = parseInt(ujpsButton.getAttribute("data-number"));
			if (!isNaN(number)) {
				ujpsButton.addEventListener("mousedown", function() {
					sendButtonMouse(number,true);
				});
				ujpsButton.addEventListener("mouseup", function() {
					sendButtonMouse(number,false);
				});
				ujpsButton.addEventListener("touchstart", function() {
					sendButtonTouch(number,true);
				});
				ujpsButton.addEventListener("touchend", function() {
					sendButtonTouch(number,false);
				});
			}
		}
	}

	let ujpsAxes = document.querySelectorAll("input[type=range]");
	for (let ujpsAxis of ujpsAxes) {
		if (ujpsAxis.hasAttribute("data-type") && ujpsAxis.hasAttribute("data-number")) {
			let dataType = ujpsAxis.getAttribute("data-type");
			let number = parseInt(ujpsAxis.getAttribute("data-number"));
			if (dataType == "axis" && !isNaN(number)) {
				ujpsAxis.addEventListener("input", function() {
					let f = 0.001 * ujpsAxis.value - 1.0;
					sendAxis(number,f);
				});
				ujpsAxis.setAttribute("min",0);
				ujpsAxis.setAttribute("max",2000);
				ujpsAxis.setAttribute("value",1000);
				sendAxis(number,0);
			}
		}
	}
})();
