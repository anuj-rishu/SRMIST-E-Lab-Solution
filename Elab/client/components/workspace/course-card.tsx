import Link from "next/link";
import { ArrowUpRight, Braces, GitBranch } from "lucide-react";
import type { Course } from "@/lib/types";
import { courseTitle, solvedInCourse } from "@/lib/format";

export function CourseCard({ course }: { course: Course }) {
  const Icon = course.COURSE_ID === 11 ? Braces : GitBranch;
  return (
    <article className="course-card">
      <div className="course-card-heading">
        <span className="course-icon">
          <Icon size={27} />
        </span>
        <span className="course-id">COURSE {course.COURSE_ID}</span>
      </div>
      <h3>{courseTitle(course)}</h3>
      <p>
        {course.COURSE_ID === 11
          ? "Build your foundations, one program at a time."
          : "Think in structures. Find a better way through."}
      </p>
      <div className="course-levels">
        {[course.LEVEL1, course.LEVEL2, course.LEVEL3].map((value, index) => (
          <div key={index}>
            <span>LEVEL 0{index + 1}</span>
            <strong>
              {Number(value || 0)}
              <small>solved</small>
            </strong>
          </div>
        ))}
      </div>
      <div className="course-card-footer">
        <span>
          <span className="blue-dot" />
          {solvedInCourse(course)}{" "}
          {solvedInCourse(course) === 1 ? "problem" : "problems"} completed
        </span>
        <Link
          href={`/dashboard/courses/${course.COURSE_ID}`}
          className="course-continue"
        >
          Continue <ArrowUpRight size={16} />
        </Link>
      </div>
    </article>
  );
}

export function CourseList({ courses }: { courses: Course[] }) {
  return (
    <section className="courses-section" id="courses">
      <div className="content-section-heading">
        <div>
          <h2>Your registered courses</h2>
        </div>
        <span className="count-label">
          {courses.length} {courses.length === 1 ? "course" : "courses"}
        </span>
      </div>
      {courses.length ? (
        <div className="course-grid">
          {courses.map((course) => (
            <CourseCard key={course._id} course={course} />
          ))}
        </div>
      ) : (
        <div className="empty-state">
          <Braces size={28} />
          <h3>No courses here yet.</h3>
          <p>Your registered E-Lab courses will appear here when available.</p>
        </div>
      )}
    </section>
  );
}
