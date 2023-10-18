# --encoding = "utf-8" --
from manim import *


class Start(MovingCameraScene):
    def _MkCharacter(self):
        head = Circle(0.5, color=BLUE, fill_opacity=1)
        eyeL = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeR = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeL.move_to(0.2 * LEFT + 0.1 * UP)
        eyeR.move_to(0.2 * RIGHT + 0.1 * UP)
        body = Polygon(
            [0, 0, 0], [-0.3, -1, 0], [0.3, -1, 0], color=BLUE, fill_opacity=1
        )
        ans = VGroup(head, body, eyeL, eyeR)
        return ans

    def _MkBackground(self):
        background = ImageMobject("background.png")

        background.scale(0.5)
        padding = ImageMobject("Screen.png").scale(0.265)
        return (background, padding)

    def _TalkBox(self, words: str, size: int):
        text = Text(words, color=WHITE, opacity=0.8).move_to([0, 0, 0])
        framebox = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            corner_radius=0.2,
            fill_color=WHITE,
        )
        return VGroup(framebox, text).scale(size)

    def construct(self):
        background, padding = self._MkBackground()
        # self.wait(5)
        background.move_to(DOWN * 2)
        padding.move_to(DOWN * 1.15)
        # self.wait(2)
        char1 = self._MkCharacter()
        char2 = self._MkCharacter()
        char1.scale(2)
        char2.scale(2)
        char1.move_to(LEFT * 10 + DOWN * 2.5)
        char2.move_to(RIGHT * 10 + DOWN * 2.5)
        self.add(char1, char2, padding, background)
        self.play(char1.animate.move_to(char1.get_center() + RIGHT * 5), run_time=3)
        talkbox = self._TalkBox(
            "\n".join(
                """
            大家好！今天我们要探讨的话题是\n
            ——多任务操作系统的实现方式。
            """.split()
            ),
            0.5,
        ).move_to(LEFT * 4 + UP * 1)
        self.play(Write(talkbox), run_time=2)
        self.wait(2)
        # self.wait(2)
        # self.play(FadeOut(talkbox), run_time=1)
        talkbox2 = self._TalkBox(
            "\n".join(
                """
            所谓多任务操作系统，就是可以\n
            在同一时间运行多个程序的操作\n
            系统。这个功能在我们日常工作\n
            和生活中非常常见，尤其是在\n
            如今这个数字化的时代。
            """.split()
            ),
            0.5,
        ).move_to(LEFT * 4 + UP * 1.4)
        self.play(ReplacementTransform(talkbox, talkbox2), run_time=1.5)
        # NextScene.construct(self, talkbox)
        img1 = ImageMobject("qq.png").scale(0.3).move_to(DOWN * 1.25)
        img2 = ImageMobject("qqMusic.png").scale(0.15).move_to(DOWN * 1 + RIGHT * 1.2)
        img3 = ImageMobject("study.png").scale(0.15).move_to(DOWN * 1.5 + LEFT)
        self.play(FadeIn(img3), run_time=1)
        self.play(FadeIn(img2), run_time=1)
        self.play(FadeIn(img1), run_time=1)
        self.wait(3)
        talkbox3 = self._TalkBox(
            "\n".join(
                """
            但是，你们知道吗？实现多任务\n
            操作系统并不简单。接下来，请\n
            电脑工程师为我们详细介绍\n
            多任务操作系统的实现方式。
            """.split()
            ),
            0.5,
        ).move_to(LEFT * 4 + UP * 1.4)
        self.remove(talkbox2)
        self.play(ReplacementTransform(talkbox2, talkbox3), run_time=1.5)
        self.play(FadeOut(img1), FadeOut(img2), FadeOut(img3))
        self.wait(2)
        self.play(FadeOut(talkbox3))
        self.play(char2.animate.move_to(char2.get_center() + LEFT * 5), run_time=3)
        self.wait(1)
        talkbox4 = self._TalkBox(
            "\n".join(
                """
        好的，首先，多任务操作系统\n
        有两种实现方式：\n
            1.抢占式\n
            2.协作式
        """.split()
            ),
            0.5,
        ).move_to(RIGHT * 4 + UP * 1.4)
        self.play(Write(talkbox4), run_time=1.5)
        self.wait(3)
        self.play(
            FadeOut(char1),
            FadeOut(background),
            FadeOut(padding),
            FadeOut(talkbox4),
            run_time=1,
        )
        # s = Polygon(
        #     [0, 0, 0], [0, 16, 0], [9, 16, 0], [9, 0, 0], color=GRAY, fill_opacity=1
        # ).move_to([0, 0, 0])
        # self.play(ReplacementTransform(padding, s))
        # r = RoundedRectangle(corner_radius=0.2, width=1.5, height=1)
        # char1.to_corner(DL)
        # char2.to_corner(DR)
        # self.play(FadeIn(char1), FadeIn(char2))
        self.wait()


class PreemptiveScheduling(Scene):
    def _MkCharacter(self):
        head = Circle(0.5, color=BLUE, fill_opacity=1)
        eyeL = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeR = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeL.move_to(0.2 * LEFT + 0.1 * UP)
        eyeR.move_to(0.2 * RIGHT + 0.1 * UP)
        body = Polygon(
            [0, 0, 0], [-0.3, -1, 0], [0.3, -1, 0], color=BLUE, fill_opacity=1
        )
        ans = VGroup(head, body, eyeL, eyeR)
        return ans

    def _TalkBox(self, words: str, size: int):
        text = Text(words, color=WHITE, opacity=0.8).move_to([0, 0, 0])
        framebox = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            corner_radius=0.2,
            fill_color=WHITE,
        )
        return VGroup(framebox, text).scale(size)

    def _Process1(self, num: int, priority: int):
        text = Text(f"Process {num}, Priority: {priority}", color=WHITE).move_to(
            [0, 0, 0]
        )
        process = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            fill_opacity=0.5,
            corner_radius=0.2,
            fill_color=BLUE,
        )
        return VGroup(process, text).scale(0.5)

    def construct(self):
        char1 = self._MkCharacter()
        char2 = self._MkCharacter()
        char1.scale(2)
        char2.scale(2)
        char1.move_to(LEFT * 10 + DOWN * 2.5)
        char2.move_to(RIGHT * 5 + DOWN * 2.5)
        self.add(char2)
        title = Text("抢占式操作系统", color=WHITE, opacity=0.8).to_corner(UL)
        self.play(Write(title))
        self.wait(1)
        talkbox1 = self._TalkBox(
            "\n".join(
                """
                抢占式操作系统是指，当一个\n
                任务需要更多的计算机资源\n
                （例如CPU时间、内存等）时，\n
                它会“抢占”其他任务正在使用的\n
                资源，以确保自己的任务可以\n
                及时完成。
                """.split()
            ),
            0.5,
        ).move_to(RIGHT * 4 + UP)
        talkbox2 = self._TalkBox(
            "\n".join(
                """
                抢占式操作系统的优点在于，
                它可以更好地保证任务的及时性
                和准确性。但是，如果一个任务
                无限期地占用了计算机资源，其他
                任务就无法运行，从而影响整个
                系统的稳定性。
                """.split()
            ),
            0.5,
        ).move_to(RIGHT * 4 + UP)
        talkbox3 = None
        self.play(TransformFromCopy(title, talkbox1))
        self.wait(2)
        process_title = self._TalkBox("Process Queue", 0.5).move_to(LEFT * 4.5 + UP * 2)
        working_title = self._TalkBox("Working Process", 0.5).move_to(
            LEFT * 0.5 + UP * 2
        )
        dashline = DashedLine([-2.5, 2.5, 0], [-2.5, -3.5, 0], color=WHITE)
        self.play(Create(process_title), Write(working_title), Write(dashline))
        priority_list = [2, 3, 1, 4, 0]
        process = [
            self._Process1(i, priority_list[i]).move_to(LEFT * 4.5 + UP * (1 - i))
            for i in range(5)
        ]
        running_process_index = -1
        running_process = None
        for i in range(len(process)):
            process[i].shift(DOWN)
            self.play(FadeIn(process[i]), process[i].animate.shift(UP))
            # self.wait(0.5)
            arrow = Arrow([0, 0, 0], [1, 0, 0], color=WHITE)
            for j in range(i + 1):
                if j == 0:
                    arrow.next_to(process[j], LEFT)
                if i == 0 or j == 0:
                    self.play(FadeIn(arrow), run_time=0.3)
                else:
                    self.play(arrow.animate.shift(DOWN), run_time=0.3)  #
                self.wait(0.2)
                priority = (
                    Text(str(priority_list[j]), color=WHITE)
                    .scale(0.5)
                    .next_to(arrow, UP)
                )
                self.play(FadeIn(priority), run_time=0.3)
                self.wait(0.2)
                self.play(FadeOut(priority), run_time=0.25)
            index = priority_list.index(min(priority_list[0 : i + 1]))
            arrow.set_color(YELLOW)
            arrow.next_to(process[index], LEFT)
            priority = (
                Text(str(priority_list[index]), color=YELLOW)
                .scale(0.5)
                .next_to(arrow, UP)
            )
            self.play(FadeIn(arrow), FadeIn(priority), run_time=0.5)
            if running_process_index != -1 and running_process_index != index:
                self.play(FadeOut(running_process), run_time=0.5)
            if running_process_index != index:
                running_process_index = index
                running_process = process[index].copy()
                running_process.move_to(LEFT * 0.5 + UP)
                self.play(TransformFromCopy(process[index], running_process))
            self.play(FadeOut(arrow), FadeOut(priority))
            if i == 2:
                self.play(ReplacementTransform(talkbox1, talkbox2))
        self.wait(2)
        self.play(
            FadeOut(talkbox2),
            FadeOut(process_title),
            FadeOut(working_title),
            FadeOut(dashline),
            FadeOut(process[0]),
            FadeOut(process[1]),
            FadeOut(process[2]),
            FadeOut(process[3]),
            FadeOut(process[4]),
            FadeOut(running_process),
            FadeOut(title),
        )


class CollaborativeScheduling(Scene):
    def _MkCharacter(self):
        head = Circle(0.5, color=BLUE, fill_opacity=1)
        eyeL = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeR = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeL.move_to(0.2 * LEFT + 0.1 * UP)
        eyeR.move_to(0.2 * RIGHT + 0.1 * UP)
        body = Polygon(
            [0, 0, 0], [-0.3, -1, 0], [0.3, -1, 0], color=BLUE, fill_opacity=1
        )
        ans = VGroup(head, body, eyeL, eyeR)
        return ans

    def _TalkBox(self, words: str, size: int):
        text = Text(words, color=WHITE, opacity=0.8).move_to([0, 0, 0])
        framebox = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            corner_radius=0.2,
            fill_color=WHITE,
        )
        return VGroup(framebox, text).scale(size)

    def _Process2(self, num: int, period: int):
        text = Text(f"Process {num}, Period: {period}", color=WHITE).move_to([0, 0, 0])
        process = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            fill_opacity=0.5,
            corner_radius=0.2,
            fill_color=BLUE,
        )
        return VGroup(process, text).scale(0.5)

    def construct(self):
        char1 = self._MkCharacter()
        char2 = self._MkCharacter()
        char1.scale(2)
        char2.scale(2)
        char1.move_to(LEFT * 10 + DOWN * 2.5)
        char2.move_to(RIGHT * 5 + DOWN * 2.5)
        self.add(char2)
        title = Text("协作式操作系统", color=WHITE, opacity=0.8).to_corner(UL)
        self.play(Write(title))
        self.wait(1)
        talkbox1 = self._TalkBox(
            "\n".join(
                """
                协作式操作系统则是指，每个
                任务都需要手动释放它所占用
                的计算机资源，否则其他任务
                无法使用这些资源。
                """.split()
            ),
            0.5,
        ).move_to(RIGHT * 4 + UP)
        talkbox2 = self._TalkBox(
            "\n".join(
                """
                协作式操作系统的优点在于，
                每个任务都有机会使用计算机
                资源，从而提高了系统的稳定性。
                但是，如果一个任务无法正常
                释放它所占用的资源，整个系统
                就会陷入死循环。
                """.split()
            ),
            0.5,
        ).move_to(RIGHT * 4 + UP)
        self.play(TransformFromCopy(title, talkbox1))
        self.wait(2)
        process_title = self._TalkBox("Process Queue", 0.5).move_to(LEFT * 4.5 + UP * 2)
        working_title = self._TalkBox("Working Process", 0.5).move_to(
            LEFT * 0.5 + UP * 2
        )
        dashline = DashedLine([-2.5, 2.5, 0], [-2.5, -3.5, 0], color=WHITE)
        self.play(Create(process_title), Write(working_title), Write(dashline))
        period_list = [2, 3, 1, 4, 2]
        process = [
            self._Process2(i, period_list[i]).move_to(LEFT * 4.5 + UP * (1 - i))
            for i in range(5)
        ]
        vg = VGroup()
        for i in range(len(process)):
            vg += process[i]
        vg.shift(DOWN)
        self.play(FadeIn(vg), vg.animate.shift(UP))
        # for i in range(len(process)):
        #     vg -= process[i]
        self.play(ReplacementTransform(talkbox1, talkbox2))
        processn = None
        for i in range(len(process)):
            period = period_list[i]
            self.play(process[i].animate.shift(RIGHT * 4))
            for j in range(i + 1, len(process)):
                self.play(process[j].animate.shift(UP), run_time=0.2)
            for j in range(period_list[i]):
                if processn != None:
                    self.remove(processn)
                processn = self._Process2(i, period - j - 1).move_to(LEFT * 0.5 + UP)
                self.play(process[i].animate.scale(1.1), run_time=0.25)
                self.play(ReplacementTransform(process[i], processn), run_time=0.25)
                process[i] = processn.copy()
            self.play(FadeOut(processn), FadeOut(process[i]))
        self.play(
            FadeOut(talkbox2),
            FadeOut(process_title),
            FadeOut(working_title),
            FadeOut(dashline),
            FadeOut(title),
            FadeOut(char2),
        )
        # vg = vgn.copy()


class Main(Scene):
    def _MkCharacter(self):
        head = Circle(0.5, color=BLUE, fill_opacity=1)
        eyeL = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeR = Circle(0.1, color=WHITE, fill_opacity=1)
        eyeL.move_to(0.2 * LEFT + 0.1 * UP)
        eyeR.move_to(0.2 * RIGHT + 0.1 * UP)
        body = Polygon(
            [0, 0, 0], [-0.3, -1, 0], [0.3, -1, 0], color=BLUE, fill_opacity=1
        )
        ans = VGroup(head, body, eyeL, eyeR)
        return ans

    def _MkBackground(self):
        background = ImageMobject("background.png")

        background.scale(0.5)
        padding = ImageMobject("Screen.png").scale(0.265)
        return (background, padding)

    def _TalkBox(self, words: str, size: int):
        text = Text(words, color=WHITE, opacity=0.8).move_to([0, 0, 0])
        framebox = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            corner_radius=0.2,
            fill_color=WHITE,
        )
        return VGroup(framebox, text).scale(size)

    def _Process1(self, num: int, priority: int):
        text = Text(f"Process {num}, Priority: {priority}", color=WHITE).move_to(
            [0, 0, 0]
        )
        process = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            fill_opacity=0.5,
            corner_radius=0.2,
            fill_color=BLUE,
        )
        return VGroup(process, text).scale(0.5)

    def _Process2(self, num: int, period: int):
        text = Text(f"Process {num}, Period: {period}", color=WHITE).move_to([0, 0, 0])
        process = SurroundingRectangle(
            text,
            buff=0.5,
            color=WHITE,
            fill_opacity=0.5,
            corner_radius=0.2,
            fill_color=BLUE,
        )
        return VGroup(process, text).scale(0.5)

    def construct(self):
        Start.construct(self)
        PreemptiveScheduling.construct(self)
        CollaborativeScheduling.construct(self)
