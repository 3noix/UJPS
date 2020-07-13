///////////////////////////////////////////////////////////////////////////////
// INIT AND CONSTANTS /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
var target = "192.168.1.40:8080"; // to provide from navbar?
//var target = "localhost:8080"; // to provide from navbar?
var msgDisplay = document.getElementById("msgDisplay");
var name = document.getElementById("name").innerHTML;
var iError = 0;
var sendRequest = true;


///////////////////////////////////////////////////////////////////////////////
// PLATFORM ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
var pf = navigator.platform;
var useTouchEvents = (pf == "iPhone");
var useMouseEvents = (pf == "Win32" || !useTouchEvents);
msgDisplay.innerHTML = pf;


///////////////////////////////////////////////////////////////////////////////
// TESTS //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
document.fullscreenEnabled = true;
var body = document.getElementById("body");

body.onfullscreenerror = function()
{
	msgDisplay.innerHTML = "full screen error";
}

window.onorientationchange = function(event)
{
	//msgDisplay.innerHTML = "Orientation is now " + event.target.screen.orientation.angle;
	msgDisplay.innerHTML = "orientation changed";
}

function requestFullScreen()
{
	//body.requestFullscreen();
	msgDisplay.innerHTML = "full screen request";
}


///////////////////////////////////////////////////////////////////////////////
// SLIDERS ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
var slider1 = document.getElementById("slider1");
var slabel1 = document.getElementById("slabel1");
slabel1.innerHTML = 0.001*slider1.value-1.0;

slider1.oninput = function()
{
	var f = 0.001 * this.value - 1.0;
	slabel1.innerHTML = f.toString().substring(0,f<0?6:5);
	sendAxis(0,f);
}

var slider2 = document.getElementById("slider2");
var slabel2 = document.getElementById("slabel2");
slabel2.innerHTML = 0.001*slider2.value-1.0;

slider2.oninput = function()
{
	var f = 0.001 * this.value - 1.0;
	slabel2.innerHTML = f.toString().substring(0,f<0?6:5);
	sendAxis(1,f);
}


///////////////////////////////////////////////////////////////////////////////
// UJPS ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
function sendButtonMouse(i,b)
{
	if (!useMouseEvents) return;
	var url = "http://" + target + "/button/" + name + "/" + i + "/" + (b ? "1" : "0");
	//console.log(url);
	if (sendRequest)
	{
		var reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
}

function sendButtonTouch(i,b)
{
	if (!useTouchEvents) return;
	var url = "http://" + target + "/button/" + name + "/" + i + "/" + (b ? "1" : "0");
	//console.log(url);
	if (sendRequest)
	{
		var reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
}

function sendAxis(i,f)
{
	var url = "http://" + target + "/axis/" + name + "/" + i + "/" + f;
	//console.log(url);
	if (sendRequest)
	{
		var reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
}

function sendPov(i,f) {
	var url = "http://" + target + "/pov/" + name + "/" + i + "/" + f;
	//console.log(url);
	if (sendRequest)
	{
		var reqhttp = new XMLHttpRequest();
		reqhttp.onerror = function() {
			iError++;
			msgDisplay.innerHTML = "An error occured (#" + iError + ")";
		}
		reqhttp.open("GET",url,true);
		reqhttp.send();
	}
}
