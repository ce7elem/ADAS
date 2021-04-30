# Telecommande
A web-based remote controller for the project ADAS.

## How does it works
The client [./client/] is a Vue.js web application. By opening it in a browser (for example on a phone), you have access to a joystick. On input, it emits a websocket packet to the server [./server/], wich will be written in a FIFO file `/tmp/rcontroller`.
This FIFO is processed by [../Controllers/Controller] process, and forwarded to the Arduino driver [../Arduino].

## Instructions
NOTE : node should be installed on your system, see the setup script at the root of the project if its not the case.
The lastest version is already build, so if you don't have any modifications to make, just run `npm i` to install the deps, and `node app.js` in the `server/` directory. The app will be avaliable at http://<RASPBERRY IP>:8080 (be sure to be in the same network than the rpi).

### Re-building the client on motification
If you made some modifications, you will have to re-build the client and replace
the files in the `server/public/` directory :
```bash
> # in the client/ directory
> npm i # install dependencies
> npm run dev # starts a developpement server : you can see your modifications in the browser until everything is ok for you
> npm run build # will produce a build/ folder with the new app files
> cd ..
>
> # here, all modifications are done, and the production files are in the client/build/ folder
> rm -rf server/public
> mv client/build server/public
>
> # all modifications are now pushed to the production environment, we can start the app 
> cd server/ 
>npm i # dont forget this
> node app.js
```
