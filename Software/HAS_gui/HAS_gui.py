from flask import Flask, render_template, jsonify, request
import serial
import threading
import time

app = Flask(__name__)

# 设置串口参数
port = 'COM4'  # 根据你的实际情况设置端口号
baudrate = 9600  # 波特率与Arduino代码中的设置一致

# 打开串口
ser = serial.Serial(port, baudrate, timeout=1)

# 全局变量用于存储温度和湿度数据
temperature = None
humidity = None


def read_serial():
    global temperature, humidity
    try:
        while True:
            try:
                # 读取一行数据并尝试解码
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                if line:
                    # 假设数据格式为 "温度: xx.xx *C 湿度: yy.yy %"
                    data = line.split(' ')
                    if len(data) >= 4:  # 检查数据长度是否足够
                        try:
                            temperature = data[1]  # 转换为浮点数
                            humidity = data[3]  # 转换为浮点数
                            print(f"Temperature: {temperature}°C, Humidity: {humidity}%")
                        except (IndexError, ValueError) as e:
                            print(f"数据处理错误: {e}, 原始数据: {line}")
                    else:
                        print("数据格式错误:", line)
                time.sleep(1)  # 添加延时，避免占用过多的CPU资源
            except UnicodeDecodeError as e:
                print(f"解码错误: {e}, 跳过该行数据")
            except Exception as e:
                print(f"未知错误: {e}")
    except KeyboardInterrupt:
        print("程序已停止")
    finally:
        if ser.is_open:
            ser.close()  # 关闭串口
        
@app.route('/')
def index():
    return render_template('index.html', temperature=temperature, humidity=humidity)

@app.route('/get_sensor_data')
def get_sensor_data():
    return jsonify({'temperature': temperature, 'humidity': humidity})

@app.route('/send_data_to_flask', methods=['POST'])
def toggle_light():
    data = request.json
    if data and data.get('status') == 'l' or data and data.get('status') == 'c' or data and data.get('status') == 'f':
        print("Light toggled!")
        ser.write(data['status'].encode('utf-8'))
        return jsonify({"message": "Light toggled successfully!"})
    return jsonify({"error": "Invalid request!"}), 400


if __name__ == '__main__':
    # 启动串口读取线程
    serial_thread = threading.Thread(target=read_serial)
    serial_thread.start()

    # 启动Flask服务器
    app.run(host='0.0.0.0', port=5000)
