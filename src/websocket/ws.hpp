#pragma once

/**
 * ## Websocket client, asynchronous
 * > char * f1 ()
 *
 * Using https://github.com/boostorg/beast
 *
 * ### Parameters
 * no parameters
 *
 * ### Returns
 *	char * : string representing heads of the ducks
 */

#include "../../Dependencies/boost/beast/core.hpp"
#include "../../Dependencies/boost/beast/websocket.hpp"
#include "../../Dependencies/boost/asio/strand.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
