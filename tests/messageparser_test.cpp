#define private public
#include "../07-GuessMyDrawing/Application/messageparser.h"
#include "../07-GuessMyDrawing/MessageType.h"

#include <QString>
#include <QVector>

// POKRETANJE:
// qmake test.pro
// make 
// dobija se izvrsni fajl test
    
TEST_CASE("fieldIsValid", "[function]"){

    SECTION("If field is undefined isFieldValid returns false."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message["typo"] = "text";
        const QJsonValue input = message.value("type"); // trying to get "type" value, but message has "typo"
            
        bool expectedOtput = false;
        
        // Act
        bool output = parser.isFieldValid(input); 

        CHECK(input.isUndefined() == true);
        CHECK(input.isNull() == false);
        
        // Assert
        REQUIRE(output == expectedOtput);
    }

      SECTION("If field is null isFieldValid returns false."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        const QString type = QString("type");
        message[type];
        const QJsonValue input = message.value(type);
            
        bool expectedOtput = false;
        
        // Act
        bool output = parser.isFieldValid(input); 
        
        CHECK(input.isUndefined() == false);
        CHECK(input.isNull() == true);

        // Assert
        REQUIRE(output == expectedOtput);
    }
    
    
    SECTION("If QJsonObject message has requiered field isFieldValid returns true."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        const QString type = QString("type");
        message[type] = QString("text");
        const QJsonValue input = message.value(type);
            
        bool expectedOtput = true;
        
        // Act
        bool output = parser.isFieldValid(input); 
        
        CHECK(input.isUndefined() == false);
        CHECK(input.isNull() == false);

        // Assert
        REQUIRE(output == expectedOtput);
    }
    
    SECTION("When called with value of type QJsonValue that does not contain a string Then return false") {
    	
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	const QJsonValue input = 42; // does not contain a string
        
        const bool expectedOutput = false;
    	 
    	// Act
    	const bool output = msgParser.isFieldValid(input);
    	
    	// Assert
    	REQUIRE(output == expectedOutput);
    	
    }
    
    SECTION("When called with value of type QJsonValue that is null Then return false") {
    	
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	const QJsonValue input = QJsonValue::Null; 
        
        const bool expectedOutput = false;
    	 
    	// Act
    	const bool output = msgParser.isFieldValid(input);
    	
    	// Assert
    	REQUIRE(output == expectedOutput);
    	
    }
    
    SECTION("When called with value of type QJsonValue that is undefined Then return false") {
    	
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	const QJsonValue input = QJsonValue::Undefined; 
        
        const bool expectedOutput = false;
    	 
    	// Act
    	const bool output = msgParser.isFieldValid(input);
    	
    	// Assert
    	REQUIRE(output == expectedOutput);
    	
    }
    
    SECTION("When called with value of type QJsonValue that contains a string Then return true") {
    	
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	const QJsonValue input = QString("test");
        
        const bool expectedOutput = true;
    	 
    	// Act
    	const bool output = msgParser.isFieldValid(input);
    	
    	// Assert
    	REQUIRE(output == expectedOutput);
    	
    }
    
}


TEST_CASE("textMessage - fuction that returns QJsonObject for text message", "[function]"){
    
    SECTION("If text is empty it'll return empty object."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        // Act
        QJsonObject message = parser.textMessage("", "me");
        
        // Assert
        REQUIRE(message.isEmpty());
    }
    
    SECTION("Message contians correct values for TYPE, CONTENT and MESSAGE_SENDER."){
        // Arrange 
        MessageParser parser = MessageParser();
        QString text = "some message";
        QString sender = "me";
        
        // Act
        QJsonObject message = parser.textMessage(text, sender);
        
        CHECK(message.length() == 3);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::TEXT_MESSAGE)==0);
        REQUIRE(message[MessageType::CONTENT].toString().compare(text)==0);
        REQUIRE(message[MessageType::MESSAGE_SENDER].toString().compare(sender)==0);
    }
}



TEST_CASE("joinRoomMessage - fuction that returns QJsonObject for joiningRoom.", "[function]"){
    
    SECTION("Message contians correct values for TYPE, ROOM_NAME and USERNAME."){
        // Arrange 
        MessageParser parser = MessageParser();
        QString username = "user";
        QString room = "game_rom";
        
        // Act
        QJsonObject message = parser.joinRoomMessage(username, room);
        
        CHECK(message.length() == 3);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::JOIN_ROOM)==0);
        REQUIRE(message[MessageType::ROOM_NAME].toString().compare(room)==0);
        REQUIRE(message[MessageType::USERNAME].toString().compare(username)==0);
    }
}



TEST_CASE("createRoomMessage - fuction that returns QJsonObject for creating new room.", "[function]"){
    
    SECTION("Message contians correct values for TYPE, ROOM_NAME, USERNAME and DURATION."){
        // Arrange 
        MessageParser parser = MessageParser();
        QString username = "user";
        QString room = "game_rom";
        int duration = 60;
        
        // Act
        QJsonObject message = parser.createRoomMessage(username, room, duration);
        
        CHECK(message.length() == 4);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::CREATE_ROOM)==0);
        REQUIRE(message[MessageType::ROOM_NAME].toString().compare(room)==0);
        REQUIRE(message[MessageType::USERNAME].toString().compare(username)==0);
        REQUIRE(message[MessageType::DURATION].toString().compare(QString::number(duration))==0);
    }
}

TEST_CASE("Construction of message for sending canvas content", "[canvasMessage][function]") {
    
    SECTION("When called with canvas content of type QString Then return QJsonObject in which TYPE is CANVAS_MESSAGE and CONTENT is set to given canvas content") {
        // Arrange
        MessageParser msgParser = MessageParser();
        QString input = QString("test");

        const QString expectedType = QString(MessageType::CANVAS_MESSAGE);
        const QString expectedContent = input;
        const int expectedMsgLength = 2;

        // Act
        QJsonObject message = msgParser.canvasMessage(input);
        const QString outputType = message[MessageType::TYPE].toString();
        const QString outputContent = message[MessageType::CONTENT].toString();
        const int outputMsgLength = message.length();

        // Assert
        CHECK(outputMsgLength == expectedMsgLength);
        REQUIRE(outputType.compare(expectedType) == 0);
        REQUIRE(outputContent.compare(expectedContent) == 0);
    }
}

TEST_CASE("leeaveRoomMessage - fuction that returns QJsonObject for leaving room.", "[function]"){
    
    SECTION("Message contians correct values for TYPE."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        // Act
        QJsonObject message = parser.leaveRoomMessage();
        
        CHECK(message.length() == 1);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::LEAVE_ROOM)==0);
    }
}



TEST_CASE("chooseWordMessage - fuction that returns QJsonObject for choosing word for next game.", "[function]"){
    
    SECTION("Message contians correct values fro TYPE and CONTENT."){
        // Arrange 
        MessageParser parser = MessageParser();
        QString word = "some_word";
        
        // Act
        QJsonObject message = parser.chooseWordMessage(word);
        
        CHECK(message.length() == 2);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::CHOOSE_WORD)==0);
        REQUIRE(message[MessageType::CONTENT].toString().compare(word)==0);
    }
}


TEST_CASE("getRooms - fuction that returns QJsonObject for asking for list of available rooms.", "[function]"){
    
    SECTION("Message contians correct values fro TYPE."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        // Act
        QJsonObject message = parser.getRoomsMessage();
        
        CHECK(message.length() == 1);
        
        // Assert
        REQUIRE(message[MessageType::TYPE].toString().compare(MessageType::GET_ROOMS)==0);
    }
}


TEST_CASE("parseReceivedMessage - function returns correct enum for received message and ret contains parameters if necessary..", "[function]"){
    
    SECTION("If message type is missing returns error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }
        
    SECTION("If message type is unknown it'll return error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;        
        message[MessageType::TYPE] = "UNKNOWN TYPE";
        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }
    
    SECTION("If text message is received without content it returns error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::TEXT_MESSAGE;
        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }
    
    SECTION("If text message is received without sender it returns error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::TEXT_MESSAGE;
        message[MessageType::CONTENT] = "some text";
        
        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }
    
    SECTION("If text message is received correctly it'll return TEXT_MESSAGE and ret vector will have two elements."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::TEXT_MESSAGE;        
        message[MessageType::CONTENT] = "some text";
        message[MessageType::MESSAGE_SENDER] = "USER";

        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::TEXT_MESSAGE;
        int expectedLength = 2;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(ret.length() == expectedLength);
        REQUIRE(expected == actual);
    }
    

    // USER JOINED
    SECTION("If user joined is received witout username returns error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::USER_JOINED;   

        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }

    
    SECTION("If user joined is correctly received it returns USER_JOINED and ret contians username."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::USER_JOINED;   
        message[MessageType::USERNAME] = "UserX";   

        QVector<QString> ret;
        int expectedLength = 1;
        
        MessageReceivedType expected = MessageReceivedType::USER_JOINED;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }

    
    // USER LEFT
    SECTION("If user left is received witout username returns error."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::USER_LEFT;   

        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::ERROR;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expected == actual);
    }

    
    SECTION("If user left is correctly received it returns USER_LEFT and ret contians username."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::USER_LEFT;   
        message[MessageType::USERNAME] = "UserX";   

        QVector<QString> ret;
        int expectedLength = 1;
        
        MessageReceivedType expected = MessageReceivedType::USER_LEFT;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }
    
    // JOIN ROOM
    SECTION("If JOIN_ROOM is received without ROOM_NAME returns ret with length 1, sayng joining failed."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::JOIN_ROOM;   

        QVector<QString> ret;
        
        MessageReceivedType expected = MessageReceivedType::JOINED_ROOM;
        int expectedLength = 1;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }

    
    SECTION(" JOIN_ROOM is received with empty ROOM_NAME returns ret with length 1, sayng joining failed."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::JOIN_ROOM;   
        message[MessageType::ROOM_NAME] = "";   

        QVector<QString> ret;
        int expectedLength = 1;
        
        MessageReceivedType expected = MessageReceivedType::JOINED_ROOM;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }
    
    SECTION(" JOIN_ROOM is received correctly it returns JOINED_ROOM and ret has no elements."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::JOIN_ROOM;   
        message[MessageType::ROOM_NAME] = "ROOM NAME";   

        QVector<QString> ret;
        int expectedLength = 0;
        
        MessageReceivedType expected = MessageReceivedType::JOINED_ROOM;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }
    
    // GET ROOMS
    SECTION("If get rooms is received correctly return GET_ROOMS and vector contains room list, 0 or more rooms. In this case 2 rooms."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::GET_ROOMS;   
        message[MessageType::CONTENT] = "ROOM1,room2";   

        QVector<QString> ret;
        int expectedLength = 2;
        
        MessageReceivedType expected = MessageReceivedType::GET_ROOMS;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }
    
    SECTION("If there's no active rooms and GET_ROOMS message is received content will be empty and ret will have length 0."){
        // Arrange 
        MessageParser parser = MessageParser();
        
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::GET_ROOMS;   
        message[MessageType::CONTENT] = "";   

        QVector<QString> ret;
        int expectedLength = 0;
        
        MessageReceivedType expected = MessageReceivedType::GET_ROOMS;
        
        // Act
        MessageReceivedType actual = parser.parseReceivedMessage(message, ret);
        
        // Assert
        REQUIRE(expectedLength == ret.length());
        REQUIRE(expected == actual);
    }
    
    SECTION("When called with message of type QJsonObject for which TYPE is GET_ROOMS and CONTENT is not valid and with ret of type QVector<QString> Then ret size is 1 and contains element \"List of rooms is missing\" and return MessageReceivedType::ERROR") {
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::GET_ROOMS;
    	// did not set message[MessageType::CONTENT] therefore CONTENT is not valid
    	
    	QVector<QString> ret;
    	const int expectedLength = 1;
  	
  	const QString expectedElement = QString("List of rooms is missing");
  		  	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::ERROR;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	REQUIRE(outLength == expectedLength); // to ensure not accessing out of bounds
    	const QString outElement = QString(ret[outLength - 1]);
    	
    	// Assert
    	REQUIRE(outElement.compare(expectedElement) == 0);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);
    
    }
    
    SECTION("When called with message of type QJsonObject for which TYPE is CANVAS_MESSAGE and CONTENT is valid and with ret of type QVector<QString> Then ret size is 1 and ret[0] contains CONTENT and return MessageReceivedType::CANVAS_MESSAGE") {
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	const QString content = QString("");
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
    	message[MessageType::CONTENT] = content;
    	
    	QVector<QString> ret;
    	const int expectedLength = 1;
    	
    	const QString expectedElement = content;
    	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::CANVAS_MESSAGE;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	REQUIRE(outLength == expectedLength); // to ensure not accessing out of bounds
    	const QString outElement = QString(ret[outLength - 1]);
    	
    	// Assert
    	REQUIRE(outElement.compare(expectedElement) == 0);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);
    }
    
    SECTION("When called with message of type QJsonObject for which TYPE is CANVAS_MESSAGE and CONTENT is not valid and with ret of type QVector<QString> Then ret size is 1 and contains element \"Canvas is missing!\" and return MessageReceivedType::ERROR") {
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
    	// did not set message[MessageType::CONTENT] therefore CONTENT is not valid
    	
    	QVector<QString> ret;
    	const int expectedLength = 1;
  	
  	const QString expectedElement = QString("Canvas is missing!");
  		  	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::ERROR;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	REQUIRE(outLength == expectedLength); // to ensure not accessing out of bounds
    	const QString outElement = QString(ret[outLength - 1]);
    	
    	// Assert
    	REQUIRE(outElement.compare(expectedElement) == 0);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);
    }
    
    SECTION("When called with message of type QJsonObject for wich TYPE is NEW_HOST and with ret of type QVector<QString> Then ret size does not change and equals to zero and return MessageReceivedType::NEW_HOST"){
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::NEW_HOST;
    	
    	QVector<QString> ret;
    	const int expectedLength = 0;
    	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::NEW_HOST;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	// Assert
    	REQUIRE(outLength == expectedLength);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);	
    	
    }
    
    SECTION("When called with message of type QJsonObject for wich TYPE is GAME_OVER and with ret of type QVector<QString> Then ret size does not change and equals to zero and return MessageReceivedType::GAME_OVER"){
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::GAME_OVER;
    	
    	QVector<QString> ret;
    	const int expectedLength = 0;
    	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::GAME_OVER;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	// Assert
    	REQUIRE(outLength == expectedLength);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);	
    	
    }
    
    SECTION("When called with message of type QJsonObject for wich TYPE is START and with ret of type QVector<QString> Then ret size does not change and equals to zero and return MessageReceivedType::GAME_START"){
    	// Arrange
    	MessageParser msgParser = MessageParser();
    	
    	QJsonObject message;
    	message[MessageType::TYPE] = MessageType::START;
    	
    	QVector<QString> ret;
    	const int expectedLength = 0;
    	
    	const MessageReceivedType expectedMessageReceivedType = MessageReceivedType::GAME_START;
    	
    	// Act
    	const MessageReceivedType outMessageReceivedType = msgParser.parseReceivedMessage(message, ret);
    	const int outLength = ret.size();
    	
    	// Assert
    	REQUIRE(outLength == expectedLength);
    	REQUIRE(outMessageReceivedType == expectedMessageReceivedType);	
    	
    }
    
    
}
