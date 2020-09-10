///////////////////////////////////////////////////////////////////////////////
// INIT AND CONSTANTS /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let msgDisplay = document.getElementById("msgDisplay");
let name = document.getElementById("name").innerHTML;
let iError = 0;


///////////////////////////////////////////////////////////////////////////////
// PLATFORM ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let pf = navigator.platform;
let useTouchEvents = (pf == "iPhone" || pf == "iPad" || pf == "Android");
let useMouseEvents = (pf == "Win32" || !useTouchEvents);
msgDisplay.innerHTML = pf;


///////////////////////////////////////////////////////////////////////////////
// TESTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
document.fullscreenEnabled = true;
let body = document.getElementById("body");

body.onfullscreenerror = function() {
	msgDisplay.innerHTML = "full screen error";
};

window.onorientationchange = function(event) {
	//msgDisplay.innerHTML = "Orientation is now " + event.target.screen.orientation.angle;
	msgDisplay.innerHTML = "orientation changed";
};

let requestFullScreen = () => {
	body.requestFullscreen();
	msgDisplay.innerHTML = "full screen request";
};


///////////////////////////////////////////////////////////////////////////////
// SLIDERS LABELS /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
{
	// slider 1
	let slider1 = document.getElementById("slider1");
	let slabel1 = document.getElementById("slabel1");
	slabel1.innerHTML = 0;
	slider1.oninput = function() {
		let f = 0.001 * this.value - 1.0;
		slabel1.innerHTML = f.toString().substring(0,f<0?6:5);
	};
	
	// slider 2
	let slider2 = document.getElementById("slider2");
	let slabel2 = document.getElementById("slabel2");
	slabel2.innerHTML = 0;
	slider2.oninput = function() {
		let f = 0.001 * this.value - 1.0;
		slabel2.innerHTML = f.toString().substring(0,f<0?6:5);
	};
}


///////////////////////////////////////////////////////////////////////////////
// UJPS ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
let sendButtonMouse = (iButton,bPressed) => {
	if (!useMouseEvents) return;
	let url = window.location.origin + "/button/" + name + "/" + iButton + "/" + (bPressed ? "1" : "0");
	let reqhttp = new XMLHttpRequest();
	reqhttp.onerror = function() {
		iError++;
		msgDisplay.innerHTML = "An error occured (#" + iError + ")";
	};
	reqhttp.open("GET",url,true);
	reqhttp.send();
};

let sendButtonTouch = (iButton,bPressed) => {
	if (!useTouchEvents) return;
	let url = window.location.origin + "/button/" + name + "/" + iButton + "/" + (bPressed ? "1" : "0");
	let reqhttp = new XMLHttpRequest();
	reqhttp.onerror = function() {
		iError++;
		msgDisplay.innerHTML = "An error occured (#" + iError + ")";
	};
	reqhttp.open("GET",url,true);
	reqhttp.send();
};

let sendAxis = (iAxis,value) => {
	let url = window.location.origin + "/axis/" + name + "/" + iAxis + "/" + value;
	let reqhttp = new XMLHttpRequest();
	reqhttp.onerror = function() {
		iError++;
		msgDisplay.innerHTML = "An error occured (#" + iError + ")";
	};
	reqhttp.open("GET",url,true);
	reqhttp.send();
};

let sendPov = (iPov,value) => {
	let url = window.location.origin + "/pov/" + name + "/" + iPov + "/" + value;
	let reqhttp = new XMLHttpRequest();
	reqhttp.onerror = function() {
		iError++;
		msgDisplay.innerHTML = "An error occured (#" + iError + ")";
	};
	reqhttp.open("GET",url,true);
	reqhttp.send();
};

// initialisation of buttons and axes
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

	let ujpsAxes = document.querySelectorAll("input[type=range][data-type][data-number]");
	for (let ujpsAxis of ujpsAxes) {
		let dataType = ujpsAxis.getAttribute("data-type");
		let dataNumber = parseInt(ujpsAxis.getAttribute("data-number"));
		if (dataType == "axis" && !isNaN(dataNumber)) {
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

