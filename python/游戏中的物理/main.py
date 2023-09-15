from manim import *
from manimlib import *
from manimpango import *
import numpy as np


class MovingDots(Scene):
    def construct(self):
        d1, d2 = Dot(color=BLUE), Dot(color=GREEN)
        dg = VGroup(d1, d2).arrange(RIGHT, buff=1)
        l1 = Line(d1.get_center(), d2.get_center()).set_color(RED)
        x = ValueTracker(0)
        y = ValueTracker(0)
        d1.add_updater(lambda z: z.set_x(x.get_value()))
        d2.add_updater(lambda z: z.set_y(y.get_value()))
        l1.add_updater(lambda z: z.become(
            Line(d1.get_center(), d2.get_center())))
        self.add(d1, d2, l1)
        self.play(x.animate.set_value(5))
        self.play(y.animate.set_value(4))
        self.wait()


class CoordSysExample(Scene):
    def construct(self):
        # the location of the ticks depends on the x_range and y_range.
        grid = Axes(
            x_range=[0, 1, 0.05],  # step size determines num_decimal_places.
            y_range=[0, 1, 0.05],
            x_length=9,
            y_length=5.5,
            axis_config={
                "numbers_to_include": np.arange(0, 1 + 0.1, 0.1),
                "font_size": 24,
            },
            tips=False,
        )

        # Labels for the x-axis and y-axis.
        y_label = grid.get_y_axis_label(
            "y", edge=LEFT, direction=LEFT, buff=0.4)
        x_label = grid.get_x_axis_label("x")
        grid_labels = VGroup(x_label, y_label)

        graphs = VGroup()
        for n in np.arange(1, 20 + 0.5, 0.5):
            graphs += grid.plot(lambda x: x ** n, color=WHITE)
            graphs += grid.plot(
                lambda x: x ** (1 / n), color=WHITE, use_smoothing=False
            )

        # Extra lines and labels for point (1,1)
        graphs += grid.get_horizontal_line(grid.c2p(1, 1, 0), color=BLUE)
        graphs += grid.get_vertical_line(grid.c2p(1, 1, 0), color=BLUE)
        graphs += Dot(point=grid.c2p(1, 1, 0), color=YELLOW)
        graphs += Tex("(1,1)").scale(0.75).next_to(grid.c2p(1, 1, 0))
        title = Title(
            # spaces between braces to prevent SyntaxError
            r"Graphs of $y=x^{ {1}\over{n} }$ and $y=x^n (n=1,2,3,...,20)$",
            include_underline=False,
            font_size=40,
        )

        self.add(title, graphs, grid, grid_labels)


ball_radius = 0.1
cube_width = 4


class ThreeDAxs(ThreeDScene):
    def construct(self):
        velocity = np.array([0.2, 0.1, 0.3])
        # self.camera_frame.animate.move_to(4 * UP)
        axe = self.CreateAxes()
        x_label = axe.get_x_axis_label("x")
        y_label = axe.get_y_axis_label("y")
        z_label = axe.get_z_axis_label("z")
        origin_point = Tex("O").move_to(
            axe.c2p(0, 0, -0.5)).rotate(
            -90 * DEGREES, axis=(0, 1, 0)).rotate(
            -90 * DEGREES, axis=(1, 0, 0))
        axe_labels = VGroup(x_label, y_label, z_label)

        self.set_camera_orientation(
            phi=75 * DEGREES,
            theta=30 * DEGREES,
            zoom=1.2,
            frame_center=axe
        )

        ball = self.CreateBall(ball_radius).move_to(
            axe.c2p(cube_width / 2, cube_width / 2,  cube_width / 2))
        cube = self.CreateCube(cube_width).move_to(
            axe.c2p(cube_width / 2, cube_width / 2, cube_width / 2))

        # self.add(axe, axe_labels, origin_point)
        # self.add(ball, cube)
        # ball.get_center()
        self.play(Write(origin_point), run_time=1)
        self.play(Create(axe), Write(axe_labels), run_time=3)
        self.add(ball, cube)
        self.wait()

    def ElasticCollision(self, ball: Sphere, velocity: list[np.ndarray], axe: ThreeDAxes, balls: list[Sphere]):
        ball_pos = axe.c2p(ball.get_center())
        surface_touched = self.SurfaceTouched(ball, axe, balls)
        if surface_touched != -1:
            velocity[surface_touched] = -velocity[surface_touched]

    def SurfaceTouched(self, ball: Sphere, axe: ThreeDAxes, balls: list[Sphere]) -> int:
        ball_pos = axe.c2p(ball.get_center())
        for i in range(0, len(ball_pos)):
            if ball_pos[i] + ball_radius >= cube_width or ball_pos[i] - ball_radius <= 0:
                return i
        return -1

    def CreateBall(self, radius: float) -> Sphere:
        return Sphere(radius=radius, resolution=(15, 32),
                      checkerboard_colors=[RED_D, RED_D], stroke_width=0)

    def CreateCube(self, width: float) -> Cube:
        return Cube(width, fill_opacity=0.2, stroke_width=2, stroke_color=GRAY)

    def CreateAxes(self):
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

        # Surface(
        #     lambda u, v: np.array([
        #         radius * np.cos(u) * np.cos(v),
        #         radius * np.cos(u) * np.sin(v),
        #         radius * np.sin(u)
        #     ]),
        #     v_range=(0, TAU),
        #     u_range=(-PI / 2, PI / 2),
        #     checkerboard_colors=[RED_D, RED_D],
        #     stroke_width=0,
        #     resolution=(15, 32))

    # def Create

# if __name__ == "__main__":
#     from os import system
#     system("manimgl {} demo -c black".format(__file__))
