using UnityEngine;
using System.Collections;

public class Star : MonoBehaviour {
	
	public string SceneName;
	bool gameFinished;

	// Use this for initialization
	void Start () {
		gameFinished = false;
	}
	
	// Update is called once per frame
	void Update () {
		GameObject	plane = GameObject.Find("Plane");

		if (gameFinished == true){
			if (Input.GetKey(KeyCode.KeypadEnter) || Input.GetKey(KeyCode.Return)) {
				if (!plane.animation.isPlaying)
					plane.animation["Level_Cleard_Animation"].time =
						plane.animation["Level_Cleard_Animation"].length;
				plane.animation["Level_Cleard_Animation"].speed = -1;
				plane.animation.Play("Level_Cleard_Animation");
				Application.LoadLevel (SceneName);
			}
		}
	}
	
	void OnTriggerEnter() {
		GameObject	textPivot = GameObject.Find("Text Pivot");
		GameObject	textBallNumber = GameObject.Find("Text Balls Number");
		GameObject	clearedLevelPlane = GameObject.Find("Plane");
		
		Debug.Log("Level finished !");
		if (clearedLevelPlane != null) {
			if (!clearedLevelPlane.animation.isPlaying)
				clearedLevelPlane.animation["Level_Cleard_Animation"].time = 0;
			clearedLevelPlane.animation["Level_Cleard_Animation"].speed = 1;
			clearedLevelPlane.animation.Play();
		}
		if (textPivot != null)
			textPivot.SetActive(false);
		if (textBallNumber != null)
			textBallNumber.SetActive(false);
		animation.Play("Animation_Disappearing_Star");
		gameFinished = true;
	}
}
