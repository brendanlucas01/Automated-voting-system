import React from 'react'
import {Row,Col,Container,Navbar,Card, Button,Alert} from "react-bootstrap"
import axios from "axios"
import { useState,useEffect } from 'react';

function ElectionPage () {
    const register_vote = (vote,voterId,event) =>{
        console.log([vote,voterId,event]);
        setSuc(true)

        axios.get(`/api/dashboard/vote?vote=${vote}&voter_id=${voterId}&event_id=${event}`)
          .then(res=>{
              console.log(res)
          })
        //   .error(err=>{
        //     console.log(err)
        //   })
        
      }
      const event=789456
      const [suc,setSuc] = useState(false)
      const [dropdown,setDropdown] = useState("")
      const [userID,setUserID] = useState("")
        const cards= [
          { id: 1, name: "BJP", value: "bjp",url:"https://1000logos.net/wp-content/uploads/2022/02/BJP-logo.png" },
          { id: 2, name: "AAP", value: "aap",url:"https://smedia2.intoday.in/indiatoday/images/stories/2015April/aap-logo_650_040815073952.jpg" },
          { id: 3, name: "INC", value: "inc",url:"https://assets.sentinelassam.com/h-upload/2020/07/01/140759-congress-logo.webp?w=940&dpr=1.3" },
        ];
  return (
    <div>
        <Navbar bg="light">
    <Container style={{justifyContent:"center"}}>
      <Navbar.Brand href="#home" style={{fontSize:"1.5em",textAlign:"center"}}>National Election 2024</Navbar.Brand>
    </Container>
  </Navbar>
      <Row>
        <Col xs={2}></Col>
        <Col xs={8}>
          {cards.map((card)=>{
            return(
              <Card key={card.value}>
          <Row>
            <Col xs={3}>

            <Card.Img variant="top" src={card.url} />
            </Col>
            <Col xs={6}>
            <Card.Body>
            <br/>
              <Card.Title style={{fontSize:"2em"}}>{card.name}</Card.Title>
              {/* <Card.Subtitle className="mb-2 text-muted">Card Subtitle</Card.Subtitle> */}
            </Card.Body>

            </Col>
            <Col xs={3}>
              <br/>
            {dropdown!==card.id&&<Button variant="success" onClick={()=>{
              setDropdown(card.id)
            }}>Vote</Button>}
            </Col>
          </Row>
            
            {dropdown===card.id
            &&<div style={{textAlign:'center'}}>
              <br></br>
              <Row>
                <Col xs={4}> 
                  <label>Kindly Enter your Voter Id:</label>
                </Col>
                <Col xs={4}>
               <input value={userID} onChange={e=>{setUserID(e.target.value)}} type="text" style={{width:"100%"}}></input>
                </Col>
                <Col xs={4}>
               <Button onClick={()=>{register_vote(card.id,userID,event)}} variant='success'>Confirm Vote</Button>
                </Col>
              </Row>
               <br/><br/>
              </div>}
    </Card>
            )
          })}
        
        </Col>
        <Col xs={2}></Col>

      </Row>
        {suc&&<Alert variant="success"> <p>The Vote for {userID} has been recorded</p></Alert>}
    </div>
  )
}

export default ElectionPage

