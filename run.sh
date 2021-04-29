#!/bin/bash

echo "# Running ADAS"
	
./ControllersController/controller ; node ./Telecommande/server/app.js ; ./Autopilot/autopilot

