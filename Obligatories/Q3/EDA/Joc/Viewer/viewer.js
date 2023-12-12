
// *********************************************************************
// Global variables
// *********************************************************************

// Viewer state.
var gamePaused = true;
var gamePreview = false; // If true, render will be called for the next tick even if game is paused, and then will be set to false.
var gameAnim = true;
var gameDirection = 1;
var actRound = 0; // Current round index.


// Data.
var raw_data_str; // String for storing the raw data.
var dataLoaded = false; // Set to true when raw_data_str is ready to be parsed.
var data = { } // Object for storing all the game data.


// Animation.
var speed = 10; // Ticks per second.
var FRAMES_PER_ROUND = 2;
var frames = 0; // Incremented each tick, when it reaches FRAMES_PER_ROUND, actRound is updated (acording to gameDirection).


// Visuals.
var unitSize = 0.6; // 1 = same size as tile.
var unitLineWidth = 2;
var grid_color = "#000000";


var cell_colors = {
  '0': "#F8A858",
  '1': "#70FF70",
  '2': "#60A8FF",
  '3': "#C0A0FF",
  'C': "#E0E0E0",
  'G': "#FFD700",
  'E': "#000000",
  'R': "#553000",
  'O': "#A0FFFF"
}


var player_colors = {
  0: "#B06020",
  1: "#008000",
  2: "#0050BB",
  3: "#8000A0"
}


// *********************************************************************
// Utility functions
// *********************************************************************

function getURLParameter (name) {
  // http://stackoverflow.com/questions/1403888/get-url-parameter-with-jquery
  var a = (RegExp(name + '=' + '(.+?)(&|$)').exec(location.search)||[,null])[1]
  if (a != null) return decodeURI(a);
  return null;
}


// Callback has a single parameter with the file contents.
function loadFile (file, callback) {
  var xmlhttp;

  if (file == null || file == "") {
    alert("You must specify a file to load.");
    return;
  }

  if (window.XMLHttpRequest) xmlhttp = new XMLHttpRequest(); // Code for IE7+, Firefox, Chrome, Opera, Safari.
  else xmlhttp = new ActiveXObject("Microsoft.XMLHTTP"); // Code for IE6, IE5.

  // http://www.w3schools.com/ajax/ajax_xmlhttprequest_onreadystatechange.asp
  xmlhttp.onreadystatechange = function() {
    // Note: We cannot check xmlhttp.status != 200 for errors because status is not set when loading local files.
    if (xmlhttp.readyState == 4) callback(xmlhttp.responseText);
  }

  xmlhttp.open("GET", file, false);
  xmlhttp.send();
}


function int (s) {
  return parseInt(s);
}


function double (s) {
  return parseFloat(s);
}


function parse_assert (read_value, expected_value) {
  var correct = (read_value == expected_value);
  if (!correct) alert("Error parsing file, expected token: " + expected_value + ", read token: " + read_value + ".");
  return correct;
}


// *********************************************************************
// Initialization functions
// *********************************************************************

function parseData (raw_data_str) {
  if (raw_data_str == "") {
    alert("Could not load game file.");
    return false;
  }

  // Convert text to tokens.
  var st = raw_data_str + "";
  var t = st.replace('\n', ' ').split(/\s+/);
  var p = 0;

  data.secgame = (t[p++] == "SecGame");

  parse_assert(t[p++], "Seed");
  data.seed = int(t[p++]);

  // Game and version.
  if (t[p++] != "Crematoria") {
    alert("Are you sure this is a Crematoria game file?");
    document.getElementById('file').value = "";
    document.getElementById('inputdiv').style.display = "";
    document.getElementById('loadingdiv').style.display = "none";
    return false;
  }

  data.version = t[p++];
  if (data.version != "1.2") alert("Unsupported game version! Trying to load it anyway.");

  parse_assert(t[p++], "nb_players");
  data.nb_players = int(t[p++]);

  parse_assert(t[p++], "nb_rounds");
  data.nb_rounds = int(t[p++]);

  parse_assert(t[p++], "nb_furyans");
  data.nb_furyans = int(t[p++]);

  parse_assert(t[p++], "nb_pioneers");
  data.nb_pioneers = int(t[p++]);

  parse_assert(t[p++], "max_nb_necromongers");
  data.max_nb_necromongers = int(t[p++]);

  parse_assert(t[p++], "nb_hellhounds");
  data.nb_hellhounds = int(t[p++]);

  parse_assert(t[p++], "nb_elevators");
  data.nb_elevators = int(t[p++]);

  parse_assert(t[p++], "gem_value");
  data.gem_value = int(t[p++]);

  parse_assert(t[p++], "turns_to_land");
  data.turns_to_land = int(t[p++]);

  parse_assert(t[p++], "rows");
  data.rows = int(t[p++]);

  parse_assert(t[p++], "cols");
  data.cols = int(t[p++]);

  data.nb_units = data.nb_players * (data.nb_furyans + data.nb_pioneers)
                  + data.max_nb_necromongers + data.nb_hellhounds;

  parse_assert(t[p++], "names");
  data.names = new Array();
  for (var i = 0; i < data.nb_players; ++i) data.names[i] = t[p++];

  data.rounds = new Array();
  for (var round = 0; round <= data.nb_rounds; ++round) {
    // Maze.
    data.rounds[round] = new Object();
    data.rounds[round].rows = new Array();
    data.rounds[round].rows[0] = new Array();
    data.rounds[round].rows[1] = new Array();
    for (var i = 0; i < data.rows; ++i) data.rounds[round].rows[0][i] = t[p++];
    for (var i = 0; i < data.rows; ++i) data.rounds[round].rows[1][i] = t[p++];

    parse_assert(t[p++], "round");
    if (int(t[p++]) != round) alert("Wrong round number!");

    // Num cells.
    parse_assert(t[p++], "nb_cells");
    data.rounds[round].nb_cells = new Array();
    for (var i = 0; i < data.nb_players; ++i) data.rounds[round].nb_cells[i] = int(t[p++]);

    // Gems.
    parse_assert(t[p++], "nb_gems");
    data.rounds[round].nb_gems = new Array();
    for (var i = 0; i < data.nb_players; ++i) data.rounds[round].nb_gems[i] = int(t[p++]);

    data.rounds[round].points = new Array();
    for (var i = 0; i < data.nb_players; ++i)
      data.rounds[round].points[i] = data.rounds[round].nb_cells[i]
                                     + data.gem_value*data.rounds[round].nb_gems[i];
    // Status.
    parse_assert(t[p++], "status");
    data.rounds[round].cpu = new Array();
    for (var i = 0; i < data.nb_players; ++i) {
      var cpu = int(double(t[p++])*100);
      data.rounds[round].cpu[i] = (cpu == -100) ? "out" : cpu + "%";
    }

    // Units.
    data.rounds[round].units = [ ];
    data.rounds[round].alive_furyans = { 0:0, 1:0, 2:0, 3:0 };
    data.rounds[round].alive_pioneers = { 0:0, 1:0, 2:0, 3:0 };
    for (var i = 0; i < data.nb_units; ++i) {
      var unit = {
        type:   t[p++],
        player: int(t[p++]),
        health: int(t[p++]),
        turns:  int(t[p++]),
        i:      int(t[p++]),
        j:      int(t[p++]),
        k:      int(t[p++]),
        move:   '' // Will be set when reading movements.
      };

      data.rounds[round].units.push(unit);
      if (unit.type == 'f') ++data.rounds[round].alive_furyans[unit.player];
      else if (unit.type == 'p') ++data.rounds[round].alive_pioneers[unit.player];
    }

    if (round != data.nb_rounds) {
      // Movements.
      parse_assert(t[p++], "movements");
      var code = int(t[p++]);
      while (code != -1) {
        data.rounds[round].units[code].move = t[p++];
        code = int(t[p++]);
      }
    }
  }
  return true;
}


// Initializing the game.
function initGame (raw_data) {
  document.getElementById("loadingdiv").style.display = "";

  // TODO: Next two calls could run concurrently.
  if (parseData(raw_data) === false) return;
  preloadImages();

  gamePaused = false;
  gamePreview = true;

  // Canvas element.
  canvas = document.getElementById('myCanvas');
  context = canvas.getContext("2d");

  // Prepare the slider.
  $("#slider").slider({
    slide: function(event, ui) {
      var value = $("#slider").slider( "option", "value" );
      actRound = value;
      frames = 0;
      gamePaused = true;
      gamePreview = true;
    }
  });
  $("#slider").width(600);
  $("#slider").slider("option", {min: 0, max: data.nb_rounds});

  // Set the listerners for interaction.
  document.addEventListener('mousewheel', onDocumentMouseWheel, false);
  document.addEventListener('keydown', onDocumentKeyDown, false);
  document.addEventListener('keyup', onDocumentKeyUp, false);

  window.addEventListener('resize', onWindowResize, false);
  onWindowResize();

  document.getElementById("loadingdiv").style.display = "none";
  document.getElementById("gamediv").style.display = "";

  mainloop();
}


function preloadImages () {
  data.img = new Array();
}


// *********************************************************************
// Main loop functions
// *********************************************************************

function updateGame () {
  $("#slider").slider("option", "value", actRound);
}


function writeGameState () {
  // Write round.
  $("#round").html("Round: " + actRound);

  // Update scoreboard.
  var scoreboard = "";
  for (var i = 0; i < data.nb_players; ++i) {
    scoreboard += "<span class='score'>"
      + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:" + cell_colors[i] + "'></div>"
      + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>" + data.names[i] + "</div>"
      + "<br/>"
      + "<div style='margin-left: 10px;'>"
      + "<div style='padding:2px;'>Cells:     " + data.rounds[actRound].nb_cells[i] + "</div>"
      + "<div style='padding:2px;'>Gems:      " + data.rounds[actRound].nb_gems[i] + "</div>"
      + "<div style='padding:2px;'>Pioneers:  " + data.rounds[actRound].alive_pioneers[i] + "</div>"
      + "<div style='padding:2px;'>Furyans:   " + data.rounds[actRound].alive_furyans[i] + "</div>"
      + (data.secgame ? "<div style='padding:2px;'>CPU: " + data.rounds[actRound].cpu[i] + "</div>" : "")
      + "</div>"
      + "</span><br/><br/>";
  }
  $("#scores").html(scoreboard);

  var order = [0, 1, 2, 3];
  for (var i = 0; i < 3; ++i) {
    for (var j = i + 1; j < 4; ++j) {
      if (data.rounds[actRound].points[order[i]] < data.rounds[actRound].points[order[j]]) {
        var k = order[i];
        order[i] = order[j];
        order[j] = k;
      }
    }
  }

  var totalboard = "";
  for (var i = 0; i < data.nb_players; ++i) {
    totalboard += "<span class='total'>"
      + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:" + cell_colors[order[i]] + "'></div>"
      + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>"
      + data.rounds[actRound].points[order[i]] + "</div>"
      + "</span><br/><br/>";
  }
  $("#totals").html(totalboard);
}


function elevator (ii, jj, inc) {
  context.strokeStyle = "#000000";
  context.fillStyle = "#000000";
  context.fillRect(jj, ii + inc, tileSize, tileSize);
  var my_gradient = context.createLinearGradient(jj, ii + tileSize + inc, jj + tileSize, ii + inc);
  my_gradient.addColorStop(0, cell_colors['E']);
  my_gradient.addColorStop(1, "#FF0000");
  context.fillStyle = my_gradient;
  context.fillRect(jj, ii + inc, tileSize, tileSize);
  context.fillStyle = "#000000";
  context.strokeRect(jj + 0.5, ii + 0.5 + inc, tileSize - 1.5, tileSize - 1.5);
}


function drawGame () {
  // Boundary check.
  if (actRound < 0) actRound = 0;
  if (actRound > data.nb_rounds) actRound = data.nb_rounds;

  // Outter Rectangle.
  context.fillStyle = grid_color;
  context.fillRect(0, 0, tileSize*data.cols, tileSize*(data.rows + 2));

  // Draw maze.
  var meitat = tileSize/2;
  var quart = tileSize/4;
  var amplada = tileSize - 0.5;
  var m = data.cols/2;             // for the circular sun
  var t1 = (2*actRound)%data.cols; // for the circular sun
  var t2 = (t1 + m - 1)%data.cols; // for the circular sun

  for (var k = 0; k < 2; ++k) {
    var rows = data.rounds[actRound].rows[k];
    var inc = 0;
    if (k == 0) inc = (data.rows + 2)*tileSize;
    for (var i = 0; i < data.rows; ++i) {
      var row = rows[i];
      for (var j = 0; j < data.cols; ++j) {
        var cell = row[j];
        var ii = i*tileSize;
        var jj = j*tileSize;
        if (cell == 'E') elevator(ii, jj, inc);
        else if (cell == 'G') {
          context.fillStyle = cell_colors['O'];
          context.fillRect(jj, ii, amplada, amplada);
          context.fillStyle = cell_colors[cell];
          var size = unitSize * tileSize * 1.2;
          var offset = (tileSize - size) / 2;
          context.beginPath();
          context.arc(jj + size/2 + offset, ii + size/2 + offset, size/2, 0, Math.PI*2, false);
          context.fill();
          context.stroke();
        }
        else if (cell != 'O') { // rock or cave, painted or not
          context.fillStyle = cell_colors[cell];
          context.fillRect(jj, ii + inc, amplada, amplada);
        }
        else {
          var night = false;
          if (t1 < t2 && j >= t1 && j <= t2) night = true;
          if (t1 > t2 && (j >= t1 || j <= t2)) night = true;
          if (night) context.fillStyle = cell_colors['O'];
          else context.fillStyle = cell_colors['G'];
          context.fillRect(jj, ii, amplada, amplada);
        }
      }
    }
  }

  if (gameAnim && frames >= FRAMES_PER_ROUND/2 && actRound < data.nb_rounds - 1) {
    rows = data.rounds[actRound].rows[1];
    ++t2;
    if (t2 == data.cols) t2 = 0;

    for (var i = 0; i < data.rows; ++i) {
      var ii = i*tileSize;
      var jj = t1*tileSize;
      var cell = rows[i][t1];
      if (cell == 'O') {
        context.fillStyle = cell_colors['G'];
        context.fillRect(jj, ii, amplada, amplada);
      }
      else elevator(ii, jj, inc);
    }

    for (var i = 0; i < data.rows; ++i) {
      var ii = i*tileSize;
      var jj = t2*tileSize;
      var cell = rows[i][t2];
      if (cell == 'O') {
        context.fillStyle = cell_colors['O'];
        context.fillRect(jj, ii, amplada, amplada);
      }
      else elevator(ii, jj, inc);
    }
  }

  // Draw units.
  context.lineWidth = unitLineWidth;
  var units = data.rounds[actRound].units;
  for (var un in units) {
    var u = units[un];
    if (u.player == -1) {
      context.strokeStyle = "#000000";
      context.fillStyle = "#000000";
    }
    else {
      context.strokeStyle = player_colors[u.player];
      context.fillStyle = player_colors[u.player];
    }
    var i = u.i;
    var j = u.j;
    var k = u.k;

    if (gameAnim) {
      // This is not perfect at the circular extrems, but it's barely perceptible.
      if (frames >= FRAMES_PER_ROUND/2) {
        if (u.move == 'b') i += 0.5;
        else if (u.move == 'w') { i += 0.5; j += 0.5; }
        else if (u.move == 'r') j += 0.5;
        else if (u.move == 'x') { i -= 0.5; j += 0.5; }
        else if (u.move == 't') i -= 0.5;
        else if (u.move == 'y') { i -= 0.5; j -= 0.5; }
        else if (u.move == 'l') j -= 0.5;
        else if (u.move == 'z') { i += 0.5; j -= 0.5; }
      }
    }

    if (u.type == 'f') drawFuryan(i, j, k);
    else if (u.type == 'p') drawPioneer(i, j, k);
    else if (u.type == 'n') {
      if (u.turns == 0) drawNecromonger(i, j);
      else if (gameAnim) {
        if (u.turns == 1) context.fillStyle = "#303030";
        else context.fillStyle = "#909090";
        context.fillRect(j*tileSize, i*tileSize, amplada, amplada);
      }
      else {
        if (u.turns == 1) context.fillStyle = "#606060";
        else context.fillStyle = "#C0C0C0";
        context.fillRect(j*tileSize, i*tileSize, amplada, amplada);
      }
    }
    else { // 'h'
      drawHellhound(i, j, "#FF0000");
      if (j == data.cols - 1) drawHellhound(i, -1, "#FF0000");
      else if (j == 0) drawHellhound(i, data.cols, "#FF0000");
    }
  }
}


function drawHellhound (i, j, col) {
  var inc = (data.rows + 2)*tileSize;
  var jm = (j-1)*tileSize;
  var j0 = j*tileSize;
  var j1 = (j+1)*tileSize;
  var j2 = (j+2)*tileSize;
  var im = (i-1)*tileSize + inc;
  var i0 = i*tileSize + inc;
  var i1 = (i+1)*tileSize + inc;
  var i2 = (i+2)*tileSize + inc;
  var size = unitSize * tileSize * 1.2;
  var offset = (tileSize - size) / 2;

  context.strokeStyle = "transparent";
  context.fillStyle = col;
  context.globalAlpha = 0.5;
  context.beginPath();
  context.moveTo(j0, im);
  context.lineTo(j1, im);
  context.lineTo(j2, i0);
  context.lineTo(j2, i1);
  context.lineTo(j1, i2);
  context.lineTo(j0, i2);
  context.lineTo(jm, i1);
  context.lineTo(jm, i0);
  context.closePath();
  context.fill();
  context.stroke();
  context.beginPath();
  context.arc(j1, i1, tileSize, 0, 0.5*Math.PI);
  context.fill();
  context.stroke();
  context.beginPath();
  context.arc(j0, i1, tileSize, 0.5*Math.PI, Math.PI);
  context.fill();
  context.stroke();
  context.beginPath();
  context.arc(j0, i0, tileSize, Math.PI, 1.5*Math.PI);
  context.fill();
  context.stroke();
  context.beginPath();
  context.arc(j1, i0, tileSize, 1.5*Math.PI, 2*Math.PI);
  context.fill();
  context.stroke();
  context.globalAlpha = 1.0;
  context.beginPath();
  context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset + inc, size/2, 0, 2*Math.PI, false);
  context.fill();
  context.stroke();
}


function drawFuryan (i, j, k) {
  var inc = 0;
  if (k == 0) inc = (data.rows + 2)*tileSize;
  var size = unitSize * tileSize * 0.5;
  var offset = (tileSize - size) / 2;
  context.beginPath();
  context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset + inc, size/2, 0, 2*Math.PI, false);
  context.fill();
  context.stroke();
  context.beginPath();
  context.moveTo(j*tileSize + offset - 0.4*size, i*tileSize + offset - 0.4*size + inc);
  context.lineTo(j*tileSize + offset + 1.4*size, i*tileSize + offset + 1.4*size + inc);
  context.stroke();
  context.beginPath();
  context.moveTo(j*tileSize + offset + 1.4*size, i*tileSize + offset - 0.4*size + inc);
  context.lineTo(j*tileSize + offset - 0.4*size, i*tileSize + offset + 1.4*size + inc);
  context.stroke();
}


function drawPioneer (i, j, k) {
  var inc = 0;
  if (k == 0) inc = (data.rows + 2)*tileSize;
  var size = unitSize * tileSize * 0.7;
  var offset = (tileSize - size) / 2;
  context.beginPath();
  context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset + inc, size/2, 0, 2*Math.PI, false);
  context.fill();
  context.stroke();
}


function drawNecromonger (i, j) {
  drawPioneer(i, j, 1);
}


// *********************************************************************
// Button events
// *********************************************************************

function playButton () {
  gamePaused = false;
}


function pauseButton () {
  gamePaused = true;
  gamePreview = true; // To call render again.
  frames = 0;
}


function startButton () {
  gamePaused = true;
  gamePreview = true;
  frames = 0;
  actRound = 0;
}


function endButton () {
  gamePreview = true;
  frames = 0;
  actRound = data.nb_rounds;
}


function animButton () {
  gameAnim = !gameAnim;
}


function closeButton () {
  window.close();
}


// *********************************************************************
// Keyboard and Mouse events
// *********************************************************************

function onDocumentMouseWheel (event) {
}


function onDocumentKeyDown (event) {
}


function onDocumentKeyUp (event) {
  // http://www.webonweboff.com/tips/js/event_key_codes.aspx
  switch (event.keyCode) {
    case 36: // Start.
      gamePreview = true;
      actRound = 0;
      frames = 0;
      break;

    case 35: // End.
      gamePreview = true;
      actRound = data.nb_rounds;
      frames = 0;
      break;

    case 33: // PageDown.
      gamePreview = true;
      actRound -= 10;
      frames = 0;
      break;

    case 34: // PageUp.
      gamePreview = true;
      actRound += 10;
      frames = 0;
      break;

    case 38: // ArrowUp.
    case 37: // ArrowLeft.
      gamePaused= true;
      gamePreview = true;
      --actRound;
      frames = 0;
      break;

    case 40: // ArrowDown.
    case 39: // ArrowRight.
      gamePaused = true;
      gamePreview = true;
      ++actRound;
      frames = 0;
      break;

    case 32: // Space.
      if (gamePaused) playButton();
      else pauseButton();
      break;

    case 72: // "h"
      help();
      break;

    default:
      // $("#debug").html(event.keyCode);
      break;
  }
}


function onWindowResize (event) {
  // Constants.
  var header_height = 150;
  var canvas_margin = 20;

  // Set canvas size.
  var size = Math.min(document.body.offsetWidth, document.body.offsetHeight - header_height) - canvas_margin*2;

  canvas.width  = size;
  canvas.height = size + 30;

  var max_dimension = Math.max(data.cols,data.rows);
  tileSize = size / max_dimension;

  drawGame();
}


function help () {
  // Opens a new popup with the help page.
  var win = window.open('help.html', 'name', 'height=400, width=300');
  if (window.focus) win.focus();
  return false;
}


// *********************************************************************
// This function is called periodically.
// *********************************************************************

function mainloop () {
  // Configure buttons.
  if (gamePaused) {
    $("#but_play").show();
    $("#but_pause").hide();
  }
  else {
    $("#but_play").hide();
    $("#but_pause").show();
  }

  if (actRound < 0) actRound = 0;

  if (actRound > data.nb_rounds) {
    actRound = data.nb_rounds;
    gamePaused = true;
    frames = 0;
  }

  if (!gamePaused || gamePreview) {
    updateGame();
    drawGame();
    writeGameState();

    if (gamePreview) {
      frames = 0;
      gamePreview = false;
    }
    else {
      ++frames;
      if (frames == FRAMES_PER_ROUND) {
        frames = 0;
        actRound += gameDirection;
      }
    }
  }

  // Periodically call mainloop.
  var frame_time = 1000/speed;
  setTimeout(mainloop, frame_time);
}


// *********************************************************************
// Main function, it is called when the document is ready.
// *********************************************************************

function init () {
  // Get url parameters.
  var game;
  if (getURLParameter("sub") != null) {
    var domain = window.location.protocol + "//" + window.location.host;
    if (getURLParameter("nbr") != null)
      game = domain + "/?cmd=lliuraments&sub=" + getURLParameter("sub") + "&nbr=" + getURLParameter("nbr") + "&download=partida";
    else
      game = domain + "/?cmd=partida&sub=" + getURLParameter("sub") + "&download=partida";
  }
  else game = getURLParameter("game");

  if (game == null || game == "") {
    // Ask the user for a game input.
    var inputdiv = document.getElementById('inputdiv')
    inputdiv.style.display = "";
    document.getElementById('file').addEventListener('change', function(evt) {
      //http://www.html5rocks.com/en/tutorials/file/dndfiles/
      var file = evt.target.files[0];
      var reader = new FileReader();
      reader.readAsText(file);
      reader.onloadend = function(evt) {
        if (evt.target.readyState != FileReader.DONE) alert("Error accessing file.");
        else { // DONE == 2.
          inputdiv.style.display = "none";
          document.getElementById("loadingdiv").style.display = "";
          initGame(reader.result);
        }
      };
    }, false);
  }
  else {
    document.getElementById("loadingdiv").style.display = "";
    // Load the given game.
    loadFile(game, initGame);
  }
}
