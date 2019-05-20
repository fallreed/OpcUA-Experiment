from opcua import ua, Server, uamethod
import logging
import time

class MyDeviceServer(object):
    def __init__(self, endpoint, name):
        # Logging configuration
        self.logger = logging.getLogger('MyDeviceServer')
        self.logger.setLevel(logging.INFO)

        # Setup server
        self.server = Server()
        self.server.import_xml("MyDevice.xml")
        self.server.set_endpoint(endpoint)
        self.server.set_server_name(name)

        self.objects_node = self.server.get_objects_node()
        self.my_device_node = self.objects_node.get_child("0:MyDevice")
        self.my_device_toggle_b = self.my_device_node.get_child("0:ToggleB")
        self.my_device_toggle_c = self.my_device_node.get_child("0:ToggleC")
        self.my_device_toggle_d = self.my_device_node.get_child("0:ToggleD")
        
        self.server.link_method(self.my_device_toggle_b, self.toggle_b)
        self.server.link_method(self.my_device_toggle_c, self.toggle_c)
        self.server.link_method(self.my_device_toggle_d, self.toggle_d)

        self.my_variable_a = self.my_device_node.get_child("0:VariableA")
        self.my_variable_b = self.my_device_node.get_child("0:VariableB")
        self.my_variable_c = self.my_device_node.get_child("0:VariableC")
        self.my_variable_d = self.my_device_node.get_child("0:VariableD")
        self.my_variable_e = self.my_device_node.get_child("0:VariableE")

    @uamethod
    def toggle_b(self, parent):
        self.logger.info("Call Toggle B method")
        self.my_variable_b.set_value(not self.my_variable_b.get_value())
        
    @uamethod
    def toggle_c(self, parent):
        self.logger.info("Call Toggle C method")
        self.my_variable_c.set_value(not self.my_variable_c.get_value())

    @uamethod
    def toggle_d(self, parent):
        self.logger.info("Call Toggle D method")
        self.my_variable_d.set_value(not self.my_variable_d.get_value())

    def start(self):
        self.server.start()

    def stop(self):
        self.server.stop()

    def setVarA(self, intNumber):
        self.my_variable_a.set_value(intNumber)

    def setVarE(self, intNumber):
        self.my_variable_e.set_value(intNumber)


if __name__ == '__main__':
    # Set logging format 
    logging.basicConfig(format='[%(asctime)s] [%(levelname)s] [%(name)s] %(message)s')

    server = MyDeviceServer("opc.tcp://0.0.0.0:4840/freeopcua/server/", "FreeOpcUa MyDevice Server")

    # simulating varA and varE value
    min_value = 0
    max_value = 100

    cnt = 0
    flag = 0

    server.start()
    
    try:
        while True:
            server.setVarA(cnt)
            server.setVarE(cnt)

            if ((cnt+1 <= max_value) and (0 == flag)):
                cnt += 1
            elif (1 == flag and (cnt-1 >= min_value)):
                cnt -= 1            
            
            if (min_value == cnt):
                flag = 0
            elif (max_value == cnt):
                flag = 1

            time.sleep(1)

    finally:
        server.stop()

