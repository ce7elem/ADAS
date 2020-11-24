GroupSources(include/boost/beast beast)
GroupSources(example/websocket/client/async "/")

add_executable (websocket-client-async
    ${BOOST_BEAST_FILES}
    Jamfile
    websocket_client_async.cpp
)

target_link_libraries(websocket-client-async
    lib-asio
    lib-beast)

set_property(TARGET websocket-client-async PROPERTY FOLDER "example-websocket-client")
