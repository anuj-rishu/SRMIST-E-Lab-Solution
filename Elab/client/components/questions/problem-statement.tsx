const headingPattern =
  /^(Problem Description|Problem Statement|Question Description|Constraints|Input Format|Output Format|Note|Sample Input|Sample Output|Examples?)\s*:/i;

export function ProblemStatement({ text }: { text: string }) {
  return (
    <div className="problem-statement">
      {text
        .split(/\n\s*\n/)
        .filter(Boolean)
        .map((paragraph, index) => {
          const match = paragraph.match(headingPattern);
          if (match) {
            const body = paragraph.slice(match[0].length).trim();
            return (
              <section key={index}>
                <h3>{match[1]}</h3>
                {body && <p>{body}</p>}
              </section>
            );
          }
          return <p key={index}>{paragraph}</p>;
        })}
    </div>
  );
}
