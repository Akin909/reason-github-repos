let component = ReasonReact.statelessComponent("RepoItem");

let make = (~repo: RepoData.repo, _children) => {
  ...component,
  render: _self =>
    <div className="repo_item">
      <a href=repo.html_url>
        <h2>
          (
            /* repo.full_name. */
            ReasonReact.stringToElement(repo.full_name)
          )
        </h2>
      </a>
      (
        ReasonReact.stringToElement(
          string_of_int(repo.stargazers_count) ++ " stars"
        )
      )
    </div>
};
