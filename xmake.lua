add_rules("mode.debug", "mode.release")
add_requires("fmt", "enet6")
add_includedirs("inc")

set_languages("c++20")
set_encodings("utf-8")

local static = true


---------------  LittleNetwork Targets --------------- 

target("LittleNetwork")
    set_kind("static")
    set_group("LittleNetwork")
    
    if static then
        add_defines("LN_STATIC")
    end
    
    add_defines("LN_COMPILE")
    add_packages("fmt", "enet6", {public = true})
    add_syslinks("ws2_32", {public = true})
    
    add_headerfiles("inc/(LittleNetwork/**.hpp)")
    add_headerfiles("inc/(LittleNetwork/**.inl)")
    add_files("src/LittleNetwork/**.cpp")

---------------  Server & Client Targets --------------- 

target("ServerTCP")
    set_group("Tests")
    set_kind("binary")
    
    if static then
        add_defines("LN_STATIC")
    end

    add_deps("LittleNetwork")
    
    add_files("src/Tests/Server/serverTCP.cpp")
    
target("ServerENet")
    set_group("Tests")
    set_kind("binary")
    
    if static then
        add_defines("LN_STATIC")
    end
    
    add_deps("LittleNetwork")
    
    add_files("src/Tests/Server/serverENet.cpp")
    
target("ClientTCP")
    set_group("Tests")
    set_kind("binary")
    
    if static then
        add_defines("LN_STATIC")
    end
    
    add_deps("LittleNetwork")
    
    add_files("src/Tests/Client/clientTCP.cpp")
    
target("ClientENet")
    set_group("Tests")
    set_kind("binary")
    
    if static then
        add_defines("LN_STATIC")
    end
    
    add_deps("LittleNetwork")
    
    add_files("src/Tests/Client/clientENet.cpp")
    
--------------- Test Targets ---------------
    
target("Serialization")
    set_group("Tests")
    set_kind("binary")
    
    add_deps("LittleNetwork")
    
    if static then
        add_defines("LN_STATIC")
    end
    
    add_files("src/Tests/Serialization/**.cpp")

