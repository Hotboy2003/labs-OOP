# import networkx as nx
# import matplotlib.pyplot as plt
#
# # Создаем направленный граф
# G = nx.DiGraph()
#
# # Добавляем ребра с метками
# G.add_edge("Достать хлеб", "Положить сыр на хлеб")
# G.add_edge("Достать сыр", "Положить сыр на хлеб")
# G.add_edge("Достать варенье", "Намазать варенье на хлеб")
# G.add_edge("Положить сыр на хлеб", "Намазать варенье на хлеб")
# G.add_edge("Намазать варенье на хлеб", "Сложить части бутерброда")
# G.add_edge("Сложить части бутерброда", "Убрать хлеб")
# G.add_edge("Сложить части бутерброда", "Убрать сыр")
# G.add_edge("Сложить части бутерброда", "Убрать варенье")
#
# # Рисуем граф
# pos = nx.circular_layout(G)
# nx.draw(G, pos, with_labels=True, node_size=500, node_color="lightblue", font_weight='bold', arrowsize=5)
#
# # Отображаем граф
# plt.show()


import networkx as nx
import matplotlib.pyplot as plt

# Создаем направленный граф
G = nx.DiGraph()

# Добавляем ребра с метками
G.add_edge("T1_W1x", "T1_W2x")
G.add_edge("T1_W2x", "T1_R3x")
G.add_edge("T2_R3y", "T2_W2y")

# Рисуем граф
pos = nx.shell_layout(G)
nx.draw(G, pos, with_labels=True, node_size=1500, node_color="lightblue", font_weight='bold', arrowsize=20)

# Отображаем граф
plt.show()