from manim import *
import numpy as np

fps = 30
load_speed = 2
total_time = 3
fps_sum = int(fps * total_time / load_speed)
ball_radius = 0.1
cube_width = 4
ball_number = 10
ball_velocity = (np.random.rand(ball_number, 3) - 0.5) * 8


def CreateBall(radius: float) -> Sphere:
    return Sphere(radius=radius, resolution=(15, 32),
                  checkerboard_colors=[RED_D, RED_D], stroke_width=0)


def CreateCube(width: float) -> Cube:
    return Cube(width, fill_opacity=0.2, stroke_width=2, stroke_color=GRAY)


def CreateAxes():
    return ThreeDAxes(
        x_range=[0, 6, 1],
        y_range=[0, 6, 1],
        z_range=[0, 6, 1],
        x_length=6,
        y_length=6,
        z_length=6,
        z_axis_config={
            "numbers_to_include": np.arange(0, 6, 1),
            "font_size": 36,
        },
        axis_config={
            "numbers_to_include": np.arange(0, 6, 1),
            "font_size": 36,
        }
    )


def GeneratePoints(n):
    points = [np.array([cube_width / 2, cube_width / 2, cube_width / 2])]
    while len(points) < n:
        new_point = np.random.uniform(ball_radius, cube_width - ball_radius, 3)

        valid = True
        for point in points:
            distance = np.linalg.norm(point - new_point)
            if distance < ball_radius * 2:
                valid = False
                break
        if valid:
            points.append(new_point)
    return points


def ReflectedVelocity(balls: list[Sphere], ball_num: int) -> int:
    balls_pos = [axe.p2c(i.get_center()) for i in balls]
    ans = np.array([0, 0, 0])
    for i in range(len(balls_pos[ball_num])):
        if balls_pos[ball_num][i] + ball_radius >= cube_width and ball_velocity[ball_num][i] >= 0:
            ans[i] = -1
        elif balls_pos[ball_num][i] - ball_radius <= 0 and ball_velocity[ball_num][i] <= 0:
            ans[i] = 1
        else:
            for j in range(ball_number):
                normal = balls[j].get_center() - balls[ball_num].get_center()
                distance = np.linalg.norm(normal)
                if distance <= ball_radius * 2 and distance != 0 and np.dot(ball_velocity[ball_num], normal) <= 0:
                    v_sum = ball_velocity[j] - ball_velocity[ball_num]
                    v_sum_normal = np.dot(v_sum, normal)

                    ball_velocity[ball_num] = ball_velocity[ball_num] + \
                        v_sum_normal * normal
                    ball_velocity[j] = ball_velocity[j] - v_sum_normal * normal
    return ans


axe = CreateAxes()
x_label = axe.get_x_axis_label("x")
y_label = axe.get_y_axis_label("y")
z_label = axe.get_z_axis_label("z")
origin_point = Tex("O").move_to(
    axe.c2p(0, 0, -0.5)).rotate(
    -90 * DEGREES, axis=(0, 1, 0)).rotate(
    -90 * DEGREES, axis=(1, 0, 0))
axe_labels = VGroup(x_label, y_label, z_label)
balls_init = GeneratePoints(ball_number)
balls = [CreateBall(ball_radius).move_to(
    axe.c2p(*balls_init[ball_num])) for ball_num in range(ball_number)]
balls_trace_path = [TracedPath(balls[ball_num].get_center, dissipating_time=1,
                               stroke_opacity=[0, 1], stroke_width=3) for ball_num in range(ball_number)]
cube = CreateCube(cube_width).move_to(
    axe.c2p(cube_width / 2, cube_width / 2, cube_width / 2))


class CreateScene(ThreeDScene):
    def construct(self):
        self.set_camera_orientation(
            phi=75 * DEGREES,
            theta=30 * DEGREES,
            zoom=1.0,
            frame_center=axe
        )

        # self.add(balls_trace_path)
        self.play(Write(origin_point), run_time=1)
        self.play(Create(axe), Write(axe_labels), run_time=3)
        self.play(DrawBorderThenFill(cube), run_time=3)
        self.wait()
        self.play(GrowFromCenter(balls[0]), run_time=1)
        self.move_camera(frame_center=balls[0], zoom=2, run_time=1)
        self.wait()
        self.wait()
        self.clear()


class ShowVelocityVect(ThreeDScene):
    def construct(self):
        self.set_camera_orientation(
            phi=75 * DEGREES,
            theta=30 * DEGREES,
            zoom=2.0,
            frame_center=balls[0]
        )
        self.add(axe, axe_labels, origin_point,
                 balls[0], cube, balls_trace_path[0])
        velocity_vect = Arrow(
            start=balls[0].get_center(), end=balls[0].get_center() + ball_velocity[0], color=WHITE, stroke_width=3)
        self.play(GrowArrow(velocity_vect), run_time=1.5)
        self.wait()
        self.clear()


class SingleBallsElasticCollision(ThreeDScene):
    def construct(self):
        total_time = 10
        fps_sum = int(fps * total_time / load_speed)
        self.set_camera_orientation(
            phi=75 * DEGREES,
            theta=30 * DEGREES,
            zoom=2.0,
            frame_center=balls[0]
        )
        velocity_vect = Arrow(
            start=balls[0].get_center(), end=balls[0].get_center() + ball_velocity[0], color=WHITE, stroke_width=3)
        self.add(axe, axe_labels, origin_point,
                 balls[0], cube, balls_trace_path[0])
        self.add(velocity_vect)
        self.move_camera(frame_center=axe, zoom=1, run_time=2, added_anims=[
                         FadeOut(velocity_vect, run_time=1.5)])
        for _ in range(fps_sum):
            self.ElasticCollision1(balls, axe)
        self.wait()
        self.play(FadeOut(balls[0], balls_trace_path[0]), run_time=1.5)
        self.clear()

    def ElasticCollision1(self, balls: list[Sphere], axe: ThreeDAxes):
        ball_number = 1
        for ball_num in range(ball_number):
            normal = ReflectedVelocity(balls, ball_num)
            if (normal != np.array([0, 0, 0])).any():
                ball_velocity[ball_num] = ball_velocity[ball_num] - 2 * \
                    np.dot(ball_velocity[ball_num], normal) / \
                    np.dot(normal, normal) * normal
        location = list(map(lambda x, y:
                            list(x * load_speed / fps) + y.get_center(), ball_velocity, balls))
        self.play(*[balls[ball_num].animate.move_to(location[ball_num])
                    for ball_num in range(ball_number)], run_time=load_speed/fps)


class MultipleBallsElasticCollision(ThreeDScene):
    def construct(self):
        total_time = 20
        fps_sum = int(fps * total_time / load_speed)
        self.set_camera_orientation(
            phi=75 * DEGREES,
            theta=30 * DEGREES,
            zoom=1.0,
            frame_center=axe
        )

        self.add(axe, axe_labels, origin_point,
                 cube, *balls_trace_path)
        self.play(*[GrowFromCenter(balls[ball_num])
                  for ball_num in range(ball_number)], run_time=1)
        for i in range(fps_sum):
            self.ElasticCollision2(balls, axe)
        self.clear()

    def ElasticCollision2(self, balls: list[Sphere], axe: ThreeDAxes):
        for ball_num in range(ball_number):
            normal = ReflectedVelocity(balls, ball_num)
            if (normal != np.array([0, 0, 0])).any():
                ball_velocity[ball_num] = ball_velocity[ball_num] - 2 * \
                    np.dot(ball_velocity[ball_num], normal) / \
                    np.dot(normal, normal) * normal
        location = list(map(lambda x, y:
                            list(x * load_speed / fps) + y.get_center(), ball_velocity, balls))
        self.play(*[balls[ball_num].animate.move_to(location[ball_num])
                    for ball_num in range(ball_number)], run_time=load_speed/fps)


class main(ThreeDScene):
    def construct(self):
        CreateScene.construct(self)
        ShowVelocityVect.construct(self)
        SingleBallsElasticCollision.construct(self)
        MultipleBallsElasticCollision.construct(self)

    def ElasticCollision1(self, balls: list[Sphere], axe: ThreeDAxes):
        ball_number = 1
        for ball_num in range(ball_number):
            normal = ReflectedVelocity(balls, ball_num)
            if (normal != np.array([0, 0, 0])).any():
                ball_velocity[ball_num] = ball_velocity[ball_num] - 2 * \
                    np.dot(ball_velocity[ball_num], normal) / \
                    np.dot(normal, normal) * normal
        location = list(map(lambda x, y:
                            list(x * load_speed / fps) + y.get_center(), ball_velocity, balls))
        self.play(*[balls[ball_num].animate.move_to(location[ball_num])
                    for ball_num in range(ball_number)], run_time=load_speed/fps)

    def ElasticCollision2(self, balls: list[Sphere], axe: ThreeDAxes):
        for ball_num in range(ball_number):
            normal = ReflectedVelocity(balls, ball_num)
            if (normal != np.array([0, 0, 0])).any():
                ball_velocity[ball_num] = ball_velocity[ball_num] - 2 * \
                    np.dot(ball_velocity[ball_num], normal) / \
                    np.dot(normal, normal) * normal
        location = list(map(lambda x, y:
                            list(x * load_speed / fps) + y.get_center(), ball_velocity, balls))
        self.play(*[balls[ball_num].animate.move_to(location[ball_num])
                    for ball_num in range(ball_number)], run_time=load_speed/fps)
