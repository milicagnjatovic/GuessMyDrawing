#include "../07-GuessMyDrawing/Server/room.h"
#include "../07-GuessMyDrawing/Server/thread.h"

TEST_CASE("Room", "[class]"){

    SECTION("The Room constructor successfully constructs the object"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;


        // Act + Assert
        REQUIRE_NOTHROW(Room(username, roomName, duration));

    }

    SECTION("Game is not started after creating Room"){
        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        const auto expected = false;


        //Act
        Room room = Room(username, roomName, duration);
        bool output = room.gameIsStarted;

        //Assert
        REQUIRE(expected == output);

    }

    SECTION("Room has ServerMessageParser that is not nullptr after creating"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        ServerMessageParser* notExpectedOutput = nullptr;


        //Act
        Room room = Room(username, roomName, duration);
        ServerMessageParser* output = room.parser;

        //Assert
        REQUIRE_FALSE(output == notExpectedOutput);        

    }

    SECTION("LeaveRoom method reduces the number of players by one"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        Thread* thread = new Thread(qintptr(2));
        const auto name2 = "Mike";
        room.players.insert(username, thread);
        room.players.insert(name2, new Thread(qintptr(3)));
        int expected = 1;

        //Act
        room.leaveRoom(thread);
        int output = room.players.size();

        //Assert
        REQUIRE(expected == output);


    }

    SECTION("After start method, the game is started"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        bool expected = true;

        //Act
        room.start();
        bool output = room.gameIsStarted;

        //Assert
        REQUIRE(expected == output);

    }

    SECTION("Method chooseRandomHost sets noMorePlayers on true if there are no players left"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        bool expected = true;

        //Act
        room.chooseRandomHost();
        bool output = room.noMorePlayers;

        //Assert
        REQUIRE(expected == output);        

    }

    SECTION("Method chooseRandomHost sets noMorePlayers on false if there are other players"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        bool expected = false;
        room.players.insert(username, new Thread(qintptr(2)));

        //Act
        room.chooseRandomHost();
        bool output = room.noMorePlayers;

        //Assert
        REQUIRE(expected == output);        

    }
    

    SECTION("Method usernameIsTaken returns true if username is already in players map"){

        //Arrange
        const auto username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
     
        room.players.insert(username, new Thread(qintptr(2)));
        bool expected = true;

        //Act
        bool output = room.usernameIsTaken(username);

        //Assert
        REQUIRE(expected == output);        

    }
    
    SECTION("Method usernameIsTaken returns false if username is not in players map"){

        //Arrange
        const auto username = "Json";
        const auto username2 = "Mike";

        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
    
        room.players.insert(username, new Thread(qintptr(2)));
        bool expected = false;

        //Act
        bool output = room.usernameIsTaken(username2);

        //Assert
        REQUIRE(expected == output);        

    }

    SECTION("Method setWordAndStartGame set chosenWord on word argument"){

        //Arrange
        const auto username = "Json";
        QString word = "phone";

        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
    

        //Act
        room.setWordAndStartGame(word);

        //Assert
        REQUIRE(word.compare(room.chosenWord)==0);

    }

    SECTION("Method checkChatWord sets the host to the sender's username if the word is score"){

        //Arrange
        QString username = "Json";
        QString word = "phone";
        Thread *sender = new Thread(qintptr(2));

        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        room.chosenWord = "phone";
        room.players.insert(username, sender);
    
        //Act
        room.checkChatWord(word, sender);

        //Assert
        REQUIRE(username.compare(room.host)==0);

    }

    SECTION("Method checkChatWord doesn't set the host to the sender's username if the word is not score"){

        //Arrange
        QString username = "Json";
        QString username2 = "Mike";

        QString word = "phone";
        Thread *sender = new Thread(qintptr(2));
        Thread *sender2 = new Thread(qintptr(5));

        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username, roomName, duration);
        room.chosenWord = "phone";

        room.players.insert(username, sender);
        room.players.insert(username2, sender2);

    

        //Act
        room.checkChatWord(word, sender2);

        //Assert
        REQUIRE_FALSE(username.compare(room.host)==0);

    }

    SECTION("After gameOver method, the game is over"){

        //Arrange
        QString username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Thread *sender = new Thread(qintptr(2));

        Room room = Room(username, roomName, duration);
        room.start();
        bool expected = false;

        //Act
        room.gameOver(sender);
        bool output = room.gameIsStarted;

        //Assert
        REQUIRE(expected == output);

    }

    SECTION("Method joinClient increases the number of players by 1 if username is not taken"){

         //Arrange
        QString username1 = "Json";
        QString username2 = "Mike";

        Thread *player1 = new Thread(qintptr(2));
        Thread *player2 = new Thread(qintptr(5));

        const auto roomName = "Game1";
        const auto duration = 0;
        Room room = Room(username1, roomName, duration);
        room.players.insert(username1, player1);
        int expected = 2;


        //Act
        room.joinClient(username2, player2);
        int output = room.players.size();

        //Assert
        REQUIRE(expected == output);

    }

    SECTION("If player is the first host in the room, method joinClient sets him as a host"){

        //Arrange
        QString username = "Json";
        const auto roomName = "Game1";
        const auto duration = 0;
        Thread *player = new Thread(qintptr(2));

        Room room = Room(username, roomName, duration);
        QString expected = username;

        //Act
        room.joinClient(username, player);
        QString output = room.host;

        //Assert
        REQUIRE(expected.compare(output) == 0);

    }


}

