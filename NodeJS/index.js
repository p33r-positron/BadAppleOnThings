#!/usr/bin/env node

const imageFolder = typeof process.argv[2] == "undefined" ? "../images/" : process.argv[2]; //Image folder is either command line argument either ../images/
const musicFile = typeof process.argv[3] == "undefined" ? "../music.mp3" : process.argv[3]; //Music location is either command line argument either ../music.mp3

const fs = require("fs");
const path = require("path");
const child_process = require("child_process");

const fps = 30;
const limit = 6570; //Number of frames + 1

var i = 1;
var time = 0;

function music()
{
	child_process.spawn("mpg123", [musicFile]);
};

function read()
{
	let n = i++;
	if(n>=limit)
		return process.exit(0);
	process.stdout.write('\033c'); //Clear Screen
	fs.readFile(path.join(imageFolder, "BA".concat(n.toString().concat(".txt"))), "utf-8", function(err, data)
	{
		if(err)
			throw "Error accessing ".concat(path.join(imageFolder, "BA".concat(n.toString().concat(".txt"))));
		else
			console.log(data);
	});
	time += 1000/fps;
};

function main()
{
	music();
	setInterval(read, 1000/fps);
};

main();
