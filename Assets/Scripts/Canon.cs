using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Canon : MonoBehaviour {
	
	public float power;
	public float minAngleLeftX;
	public float maxAngleRightX;
	public int maximum_balls;

	public GameObject ballEmiter;
	public GameObject ball;
	public GameObject canonBody;
	public GameObject left;
	public GameObject right;
	public GameObject smoke;
	
	public float angleX;
	
	public List<GameObject> ballList;
	
	bool fire;
	
	// Use this for initialization
	void Start () {
		Quaternion rot=new Quaternion();
       	rot.eulerAngles = transform.eulerAngles;
       	canonBody.transform.rotation=rot;
		canonBody.transform.RotateAround(canonBody.transform.position, new Vector3(1, 0, 0), angleX);
		fire = false;
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
				ballList[0].transform.position = Vector3.down * 100;
				GameObject ballToRemove = ballList[0];
				ballList.RemoveAt(0);
				Destroy(ballToRemove, 1);
			}
		}
		if (Input.GetKey(KeyCode.RightArrow)) {
			if ( angleX < maxAngleRightX ) {
				canonBody.transform.RotateAround(canonBody.transform.position, new Vector3(1, 0, 0), 1f);
				angleX++;
			}
		}
		if (Input.GetKey(KeyCode.LeftArrow)) {
			if ( angleX > minAngleLeftX ) {
				canonBody.transform.RotateAround(canonBody.transform.position, new Vector3(1, 0, 0), -1f);
				angleX--;
			}
		}
		if (Input.GetKeyDown(KeyCode.Space)) {
			fire = true;
			canonBody.animation.Play();
			left.animation.Play();
			right.animation.Play();
			Instantiate(smoke, ballEmiter.transform.position, Quaternion.identity);
		}
	}
}
