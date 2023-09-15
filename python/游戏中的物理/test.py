import numpy as np
from pprint import pprint

# def collision_velocity(v1, v2, n):
#     v_rel = v2 - v1
#     v_rel_normal = np.dot(v_rel, n)

#     v1_new = v1 + v_rel_normal * n
#     v2_new = v2 - v_rel_normal * n

#     return v1_new, v2_new


# # 示例用法
# m1 = 1.0
# m2 = 1.0
# v1 = np.array([1.0, 2.0, 3.0])
# v2 = np.array([-1.0, -2.0, -3.0])
# n = np.array([0.0, 1.0, 0.0])  # 碰撞平面的法向量

# v1_new, v2_new = collision_velocity(m1, m2, v1, v2, n)
# print("碰撞后小球1的速度向量:", v1_new)
# print("碰撞后小球2的速度向量:", v2_new)

# l = [np.array([2, 1, 3]),
#      np.array([1, 2, 3]),
#      np.array([1, 3, 2]),
#      np.array([2, 3, 1]),
#      np.array([3, 2, 2])]

# print((l[0] != l[1]).any())

# tmp = (np.random.rand(5, 3) - 0.5) * 10
# print(tmp)

# def test(l: list[np.array]):
#     l[0] = np.array([0, 0, 0])
#     print(l)


# # test(l)
# tmp = list(map(lambda x: x * 2, l))
# print(tmp)
# print(l)

# def reflect_vector(vector, normal):
#     dot_product = np.dot(vector, normal)
#     norm_squared = np.dot(normal, normal)
#     reflection = vector - 2 * \
#         np.dot(vector, normal) / \
#         np.dot(normal, normal) * normal
#     # reflection = vector - 2 * dot_product / norm_squared * normal
#     return reflection


# # 示例用法
# vector = np.array([3, 0, 0])  # 待反转的向量
# normal = np.array([-1, 0, 0])  # 参考向量或法线向量

# reflected_vector = reflect_vector(vector, normal)
# print("反转后的向量:", reflected_vector)

def generate_points(n):
    points = []
    while len(points) < n:
        new_point = np.random.uniform(0, 4, 3)

        valid = True
        for point in points:
            distance = np.linalg.norm(point - new_point)
            if distance < 0.1 * 2:
                valid = False
                break
        if valid:
            points.append(new_point)
    return points


pprint(generate_points(5))
