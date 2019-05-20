from opcua import Client, ua
from opcua.ua import ua_binary as uabin
from opcua.common.methods import call_method

class MyDeviceClient:
    def __init__(self, endpoint):
        self.client = Client(endpoint)

    def __enter__(self):
        self.client.connect()
        return self.client

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.client.disconnect()


if __name__ == '__main__':
    with MyDeviceClient("opc.tcp://localhost:4840/freeopcua/server/") as client:
        root = client.get_root_node()
        print("Root node is: ", root)
        objects = client.get_objects_node()
        print("Objects node is: ", objects)

        MyDevice = objects.get_child("0:MyDevice")
        print("MyDevice is: ", MyDevice)

        resulting_text = MyDevice.call_method("0:ToggleB")
        print(resulting_text)

        # resulting_text = MyDevice.call_method("0:ToggleC")
        # print(resulting_text)

        # resulting_array = MyDevice.call_method("0:ToggleD")
        # print(resulting_array)

