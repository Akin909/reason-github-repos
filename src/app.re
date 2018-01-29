type state = {repo: option(array(RepoData.repo))};

type action =
  | Loaded(array(RepoData.repo));

let component = ReasonReact.reducerComponent("App");

let dummyRepo: array(RepoData.repo) = [|
  RepoData.parseRepoJson(
    Js.Json.parseExn(
      {js|
    {
      "stargazers_count": 27,
      "full_name": "jsdf/reason-react-hacker-news",
      "html_url": "https://github.com/jsdf/reason-react-hacker-news"
    }
    |js}
    )
  )
|];

let make = _children => {
  ...component,
  initialState: () => {repo: None},
  didMount: ({reduce}) => {
    let handleReposLoaded = reduce(repoData => Loaded(repoData));
    RepoData.fetchRepos()
    |> Js.Promise.then_(repoData => {
         handleReposLoaded(repoData);
         Js.Promise.resolve();
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  reducer: (action, _state) =>
    switch action {
    | Loaded(loadedRepo) => ReasonReact.Update({repo: Some(loadedRepo)})
    },
  render: ({state}) => {
    let repoItems =
      switch state.repo {
      | Some(repos) =>
        ReasonReact.arrayToElement(
          Array.map(
            (repo: RepoData.repo) => <RepoItem key=repo.full_name repo />,
            repos
          )
        )
      | None => ReasonReact.stringToElement("Loading...")
      };
    <div className="App">
      <h1 className="title">
        (ReasonReact.stringToElement("Reason Projects"))
      </h1>
      <div className="repos_container"> repoItems </div>
    </div>;
  }
};
