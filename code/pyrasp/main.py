import pypath
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
        if OK in ans:
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

class Coordinates():
    def __init__(self, x=0 ,y=0):
        self.x = x
        self.y = y

class RobotProtocol():
    def __init__(self):
        self.robot = Communication()
        self.robot.start()
    
    def go_to(self, x : float, y: float):
        command = "SPO" + str(int(x*100)) + "," + str(int(y*100)) 
        self.robot.send(command)
        self.robot._read() # to be removed
    
    def set_angle(self, angle: int):
        command = "SRO" + str(angle)
        self.robot.send(command)
        self.robot._read() # to be removed
        
class Robot():
    def __init__(self):
        self.goals = [Coordinates(0.5, 0.5),
                      Coordinates(2.5, 1.5),
                      Coordinates(2.5, 0.5),
                      Coordinates(0.5, 0.5)]
        self.protocol = RobotProtocol()
    
    def run(self):
        for destination in self.goals:
            self.protocol.go_to(destination.x, destination.y)

if __name__ == "__main__":
    robot = Robot()
    robot.run()