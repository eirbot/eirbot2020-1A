


class DummyCommunication():
    def __init__(self, serial_port='/dev/ttyACM0', com_speed=921600):
        pass
    
    def send(self, data):
        pass
    
    def _write(self, command):
        pass
    def _read(self):
        pass
    
    def _check_answer(self):
        pass
    
    def run(self):
        pass
            
    def is_something_recived(self):
        pass
    
    def get_last_recived_frame(self):
        pass
    
    def stop(self):
        pass

    def start(self):
        pass