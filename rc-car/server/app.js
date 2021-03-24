const app = require('express')();
const http = require('http').createServer(app);
var io = require('socket.io')(http);

const fs = require('fs');


const in1 = 13
const in2 = 15
const in3 = 16
const in4 = 18


const Gpio = require('onoff').Gpio;

let dir = {
	right: new Gpio(in1, 'out'),
	right_back: new Gpio(in2, 'out'),
	left: new Gpio(in3, 'out'),
	left_back: new Gpio(in4, 'out'),
}
 
// button.watch((err, value) => led.writeSync(value));



io.on('connection', function (socket) {

	socket.on('forward', function (data) {
		console.log("forward")

		zero().then(function(){
			dir.right.writeSync(1)
			dir.left.writeSync(1)
			console.log(require('util').inspect(dir))

		})
	});

	socket.on('right', function (data) {
		console.log("right")

		zero().then(function(){
			dir.right.writeSync(1)
			console.log(require('util').inspect(dir))

		})
	});

	socket.on('left', function (data) {
		console.log("left")

		zero().then(function(){
			dir.left.writeSync(1)
			console.log(require('util').inspect(dir))

		})
	});

	socket.on('backward', function (data) {
		console.log("backward")

		zero().then(function(){
			dir.right_back.writeSync(1)
			dir.left_back.writeSync(1)
			console.log(require('util').inspect(dir))

		})
	});

	socket.on('end', function (data) {
		console.log("end")

		zero()
	});
});


let zero = async function(){
	return new Promise(resolve=>{
		dir.right.writeSync(false)
		dir.right_back.writeSync(false)
		dir.left.writeSync(false)
		dir.left_back.writeSync(false)

		resolve();		
	})
}


process.on('SIGINT', _ => {
	dir.right.unexport();
	dir.right_back.unexport();
	dir.left.unexport();
	dir.left_back.unexport();
});

app.use(function(req, res, next) {
	res.header("Access-Control-Allow-Origin", "*");
	res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
	next();
});

app.use(require('express').static(__dirname + '/public'));

app.get('/', (req, res) => {
	res.sendFile(__dirname + '/index.html');
	console.log("New client");
});


http.listen(80, function(){
	console.log('listening on *:80');
});
