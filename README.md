# Алгоритмический аппарат используемый в GPS приемнике

1. Генерация CA кода
	* Вход: PRN
	* Выход: 1023 бит кода

2. Коррелятор
	* Вход: Сгенерированный CA код и "принятый" сигнал, содержащий CA + 16 байта NAV навигационной  информации после каждых 1023 бит CA кода. Принятый сигнал содержится в файле: первой строкой количество N циклов CA+NAV в последующих N*(1023+128).
	* Выход: сдвиг в битах запаздывание принятого сигнала относительного сгенерированного

3. Нахождение PRN по входным данным
	* Вход: "принятый" сигнал, содержащий CA + 16 байта NAV навигационной   информации после каждых 1023 бит CA кода. Принятый сигнал содержится в файле: первой строкой N - количество циклов CA+NAV в последующих  N*(1023+128) бит.
	* Выход: PRN

4. Вычисление положения спутника по параметрам орбиты/
	* Вход: параметры круговой орбиты - координаты центра, радиус, угловая скорость, время
	* Выход: x и y спутника

5. Триангуляция,  нахождение координат приемника по расстояниям до спутников
	* Вход: координаты спутников и расстояния до них.
	* Выход: x и y приемника

![](https://github.com/xitowzys/GPS-receiver/raw/master/raw/1.jpg)
![](https://github.com/xitowzys/GPS-receiver/raw/master/raw/2.jpg)
![](https://github.com/xitowzys/GPS-receiver/raw/master/raw/CA.png)
