// define alowing us to test private methods:
#define private public
#include "../07-GuessMyDrawing/Application/messageparser.h"
#include "../07-GuessMyDrawing/Application/client.h"

#include <QString>


TEST_CASE("client", "[constructor]"){

    SECTION("Clinet is not host after creating."){
        // Arrange 
        Client client("milica");
        bool expectedOtput = true;
        
        // Act
        bool output = client.isHost(); 

        // Assert
        REQUIRE(output == expectedOtput);
    }
    
    
    SECTION("Clinet has messageSocket that is not nullptr after creating."){
        // Arrange 
        Client client("milica");
        QTcpSocket * notExpectedOtput = nullptr;
        
        // Act
        QTcpSocket *output = client.messageSocket; 

        // Assert
        REQUIRE(output != notExpectedOtput);
    }
}
    
TEST_CASE("client.joinRoom", "[function]"){
    SECTION("Client's name sets after joining room."){
        // Arrange 
        Client client("milica");
        QString name = "me";
        QString room = "room";
        
        // Act
        client.joinRoom(name, room);
        QString nameAfterJoin = client.mName;
        
        // Assert
        REQUIRE(name.compare(nameAfterJoin)==0);
    }
}
  
TEST_CASE("client.leaveRoom", "[function]"){
    SECTION("Client who was host won't be host anymore after leaving room."){
        // Arrange 
        Client client("milica");
        client.imHost = true;
        
        // Act
        client.leaveRoom();
        bool afterLeaving = client.isHost();
        
        // Assert
        REQUIRE(afterLeaving == false);
    }

            
    SECTION("Client who was not host is not host after leaving room."){
        // Arrange 
        Client client("milica");
        client.imHost = false;
        
        // Act
        client.leaveRoom();
        bool afterLeaving = client.isHost();
        
        // Assert
        REQUIRE(afterLeaving == false);
    }
}
