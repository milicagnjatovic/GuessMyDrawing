#define private public
#include "../07-GuessMyDrawing/Server/server.h"
#include "../07-GuessMyDrawing/Server/room.h"
#include "../07-GuessMyDrawing/Server/thread.h"

TEST_CASE("Server", "[class]") {

    SECTION("Function getRoomFromThread returns a room correctly if the given thread is in a room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        thread->setRoomName(room_name);
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        // Act
        Room* expected_room = s.getRoomFromThread(thread);
        // Assert
        REQUIRE(expected_room == room);
    }

    SECTION("Function getRoomFromThread returns nullptr if the given thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        // Act
        Room* expected_room = s.getRoomFromThread(thread);
        // Assert
        REQUIRE(expected_room == nullptr);
    }

    SECTION("Function createRoom will increment _rooms map size") {
        // Arrange
        Server s;
        const QString room_name = "test_room";
        const QString username = "test_username";
        const int duration = 123;
        int rooms_size = s._rooms.size(); 
        // Act
        s.createRoom(username, room_name, duration);
        // Assert
        REQUIRE(s._rooms.size() == rooms_size + 1);
    }

    SECTION("Function joinRoom will set a thread room name to a given room name if thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        // Act
        s.joinRoom(username, room_name, thread);
        // Assert
        REQUIRE(thread->getRoomName() == room_name);
    }

    SECTION("Function joinRoom will change rooms if thread was already in a room before.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name1 = "test_room1";
        const QString username1= "test_username1";
        const QString room_name2 = "test_room2";
        const QString username2 = "test_username2";
        Room* room1 = new Room(room_name1, username1, 60);
        Room* room2 = new Room(room_name2, username2, 60);
        thread->setRoomName(room_name1);
        s._rooms.insert(room_name1, room1);
        s._rooms.insert(room_name2, room2);
        // Act
        s.joinRoom(username2, room_name2, thread);
        // Assert
        REQUIRE(thread->getRoomName() == room_name2);
    } 

    SECTION("Function joinRoom will throw exception if the room doesn't exist.") {
         // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        const QString room_name2 = "room_that_doesn't_exist";
        // Act+Assert
        REQUIRE_THROWS(s.joinRoom(username, room_name2, thread));
    }

    SECTION("Function leaveRoom will change room_name to "" if thread was in a room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        s.joinRoom(username, room_name, thread);
        // Act
        s.leaveRoom(thread);
        // Assert
        REQUIRE(thread->getRoomName() == "");
    }

    SECTION("Function leaveRoom throws an exception if thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        // Act + Assert
        REQUIRE_THROWS(s.leaveRoom(thread));
    }

    SECTION("Function chooseWord sets a word in room correctly if thread is in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        const QString word = "test";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        s.joinRoom(username, room_name, thread);
        // Act
        s.chooseWord(word, thread);
        // Assert
        REQUIRE(room->getWord() == word);
    }

    SECTION("Function chooseWord throws an exception if thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        const QString room_name = "test_room";
        const QString username = "test_username";
        const QString word = "test";
        Room* room = new Room(room_name, username, 60);
        s._rooms.insert(room_name, room);
        // Act + Assert
        REQUIRE_THROWS(s.chooseWord(word, thread));
    }

    SECTION("Function broadcastMessage throws an exception if thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::TEXT_MESSAGE;
        // Act + Assert
        REQUIRE_THROWS(s.broadcastMessage(message, thread));
    }

    SECTION("Function broadcastCanvas throws an exception if thread is not in any room.") {
        // Arrange
        Server s;
        Thread* thread = new Thread(quintptr(123));
        QJsonObject message;
        message[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
        // Act + Assert
        REQUIRE_THROWS(s.broadcastMessage(message, thread));
    }

    SECTION("Function getRooms returns a string of room names divided by ,.") {
        // Arrange
        Server s;
        const QString room_name1 = "test_room1";
        const QString username1 = "test_username1";
        const QString room_name2 = "test_room2";
        const QString username2 = "test_username2";
        const QString room_name3 = "test_room3";
        const QString username3 = "test_username3";
        const int duration = 123;
        Room* room1 = new Room(room_name1, username1, duration);
        Room* room2 = new Room(room_name2, username2, duration); 
        Room* room3 = new Room(room_name3, username3, duration); 
        s._rooms.insert(room_name1, room1);
        s._rooms.insert(room_name2, room2);
        s._rooms.insert(room_name3, room3);
        QString expected_rooms = "test_room1,test_room2,test_room3"; 
        // Act
        QString received_rooms = s.getRooms();
        // Assert
        REQUIRE(expected_rooms == received_rooms);
    }

    SECTION("Function getRooms returns a string without , if there is only one room.") {
        // Arrange
        Server s;
        const QString room_name1 = "test_room1";
        const QString username1 = "test_username1";
        const int duration = 123;
        Room* room1 = new Room(room_name1, username1, duration);
        s._rooms.insert(room_name1, room1);
        QString expected_rooms = "test_room1"; 
        // Act
        QString received_rooms = s.getRooms();
        // Assert
        REQUIRE(expected_rooms == received_rooms);
    }

    SECTION("Function getRooms returns an empty string if there are no rooms.") {
        // Arrange
        Server s;
        QString expected_rooms = ""; 
        // Act
        QString received_rooms = s.getRooms();
        // Assert
        REQUIRE(expected_rooms == received_rooms);
    }
}