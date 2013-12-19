using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Canon : MonoBehaviour {
	
	public float power;
	public int minAngleLeftX;
	public int maxAngleRightX;
	public int maximum_balls;
	public int optimumBalls;
	int ballsCount;

	public GameObject ballEmiter;
	public GameObject ball;
	public GameObject canonBody;
	public GameObject left;
	public GameObject right;
	public GameObject smoke;
	public GameObject particleSystemBallDisappear;
	
	public float angleX;
	
	public List<GameObject> ballList;
	
	bool fire;
	float incAngle;
	
	// Use this for initialization
	void Start () {
		fire = false;
		incAngle = 0;
		ballsCount = 0;
	}
	
	// Update is called once per frame
	void Update () {
		if (fire && !canonBody.animation.isPlaying && !left.animation.isPlaying && !right.animation.isPlaying) {
			GameObject nextBall = (GameObject) Instantiate(ball, ballEmiter.transform.position, Quaternion.identity);
			Vector3 dir = ballEmiter.transform.position - canonBody.transform.position;
			dir *= power;
			nextBall.rigidbody.AddForce(dir, ForceMode.Impulse);
			fire = false;
			ballList.Add(nextBall);
			if (ballList.Count > maximum_balls)
			{
				Instantiate(particleSystemBallDisappear, ballList[0].transform.position, Quaternion.identity);
				ballList[0].transform.position = Vector3.down * 100;
				GameObject ballToRemove = ballList[0];
				ballList.RemoveAt(0);
				Destroy(ballToRemove, 1);
			}
			ballsCount++;
		}
		angleX = canonBody.transform.localEulerAngles.z;
		if (Input.GetKey(KeyCode.RightArrow)) {
			if (incAngle <= 1)
				incAngle += 0.1f;
			float cmp = angleX + incAngle;
			if (cmp > 180) {
				cmp -= 360;
			}
			if ( cmp < maxAngleRightX ) {
				canonBody.transform.RotateAround(canonBody.transform.position, new Vector3(1, 0, 0), incAngle);
			}
		} else if (Input.GetKey(KeyCode.LeftArrow)) {
			if (incAngle <= 1)
				incAngle += 0.1f;
			float cmp = angleX - incAngle;
			if (cmp <= 0.1) {
				cmp += 360;
			}
			if ( cmp > minAngleLeftX ) {
				canonBody.transform.RotateAround(canonBody.transform.position, new Vector3(1, 0, 0), -incAngle);
			}
		} else {
			incAngle = 0;
		}
		if (Input.GetKeyDown(KeyCode.Space)) {
			fire = true;
			audio.Play(22050);
			canonBody.animation.Play();
			left.animation.Play();
			right.animation.Play();
			Instantiate(smoke, ballEmiter.transform.position, Quaternion.identity);
		}
	}
	
	void ResetAll()
	{
		int i = 0;
		ballsCount = 0;
		List<GameObject> destroyList = new List<GameObject>();
		
		while (i < ballList.Count) {
			Instantiate(particleSystemBallDisappear, ballList[i].transform.position, Quaternion.identity);
			ballList[i].transform.position = Vector3.down * 100;
			destroyList.Add(ballList[i]);
			++i;
		}
		ballList.RemoveAll( (ball) => { return true; } );
		foreach (GameObject ball in destroyList)
		{
			Destroy(ball, 1);
		}
	}
	
	public void setGrade(){
		GameObject scoreTextObj = GameObject.Find("Text Stars");
		TextMesh scoreText = (TextMesh)scoreTextObj.GetComponent("TextMesh");
		
		if (ballsCount <= optimumBalls)
			scoreText.text = "* * *";
		else if (ballsCount > optimumBalls && ballsCount <= optimumBalls*2)
			scoreText.text = "* * _";
		else
			scoreText.text = "* _ _";
	}
}
