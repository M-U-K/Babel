The project consists of a client/server architecture for voice over IP applications, similar to Skype or TeamSpeak.
with our own communication protocol.


Category: Communication protocol                                       
Epitech 2021                                                           N. Peter
                                                                       G. Soisson
                                                                       G. Debard
                                                                       M. Payant

                                Babel Protocol

Abstract
    
    This document provide a complete documentation for the communication
    between the server and client on the Epitech project's babel.

Introduction
    
    This document provide all information for our project about communication.
    Our goal is to provide a good protocol that allow us, to creat a new command
    easily and improve the existing one.

Syntax
    
    Each command is composed by a tag a space and a value and terminated by
    \r\n.
    [Command] [Space] [Value]
    Example: CONNECT ['user_name']\r\n

Command and return
    
    When you send a command to the server it send back a command you have to
    read. This command is composed by a code a space and a description ended
    by \r\n.
    [Code] [Space] [Description]\r\n
    101 ['uuid user_name']\r\n

List of command

    CONNECT ['user_name']                   Connection to the server
    OUT     []                              Disconnection from the current
                                            server
    USERS   []                              Return all clients
    CALL    ['sender_name']                 Start call to another client
    CALLED  ['caller_name']                 Inform a client there is income call
    ACCEPT  ['target_name']                 Target accept income call
    HANGUP  ['target_name']                 Client decline income call
    NEW     ['user_name']                   Create new Client

List of return

    101     Connection successful
    401     Connection denied
    102     Disconnection successful
    103     List of users
    104     Send Call success
    404     Send Call fail
    105     Income call
    106     Call started
    107     Call denied successfully
    108     User created
    408     User creation failed
