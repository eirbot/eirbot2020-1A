from pypath import Coordinates, Size, Rectangle, Field, Castar
import serial
import time
import threading
import queue

class Communication(threading.Thread):
    def __init__(self, serial_port='/dev/ttyACM0', com_speed=921600):
        self.serial = serial.Serial(serial_port, baudrate=com_speed)
        self.to_send = queue.Queue()
        self.recived = queue.Queue()
        self.running = True
        self.debug = True
        super().__init__()
    
    def send(self, data):
        print("Sending", data)
        self.to_send.put(data + "\n")
    
    def _write(self, command):
        if not isinstance(command, str):
            command = str(command)
        self.serial.write(command.encode())
    
    def _read(self):
        readed = self.serial.read_until(b'\n')
        if self.debug: print(readed)
        return readed
    
    def _check_answer(self):
        ans = self._read()
        if "OK" in ans:
            return True
        return False
    
    def run(self):
        while self.running:
            if self.to_send.qsize():
                self._write(self.to_send.get(block=True))
                self._check_answer()
            
    def is_something_recived(self):
        return len(self.recived) >= 0

    def get_last_recived_frame(self):
        return self.recived.get()
    
    def stop(self):
        self.running = False

class RobotProtocol():
    def __init__(self):
        self.robot = Communication()
        self.robot.start()
    
    def go_to(self, x , y):
        if isinstance(x, float):
            x = int(x*100)
        if isinstance(y, float):
            y = int(y*100)
        
        command = "SPO" + str(x) + "," + str(y) 
        self.robot.send(command)
        self.robot._read() # to be removed
    
    def set_angle(self, angle: int):
        command = "SRO" + str(angle)
        self.robot.send(command)
        self.robot._read() # to be removed
  
  
class CtfBoard():
    def __init__(self):
        self.width = 300
        self.height = 200
        self.board = Field(self.width , self.height, 34)
        cup_size = Size(3, 3)
        list_obstacle = [Rectangle(Coordinates(self.width/2, self.height/2), cup_size)]
        for obstacle in list_obstacle:
            self.board.add_obstacle(obstacle)
        
        self.astar = Castar()
        
        
        
    def get_path(self, pos_from, pos_to):
        status, path = self.astar.find_path_simplified(pos_from, pos_to, self.board)
        print("Astar status ", status)
        return path
        
      
class Robot():
    def __init__(self, board : CtfBoard):
        self.pos = Coordinates(16, 80)
        self.goals = [Coordinates(250, 80), Coordinates(40, 160)]
        self.protocol = RobotProtocol()
        self.board = board
    
    def run(self):
        for destination in self.goals:
            path = self.board.get_path(self.pos, destination)
            for waypoint in path:
                self.protocol.go_to(waypoint.x, waypoint.y)




if __name__ == "__main__":
    board = CtfBoard()
    robot = Robot(board)
    robot.run()